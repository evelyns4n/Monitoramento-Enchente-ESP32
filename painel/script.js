/*
 * Painel de monitoramento de enchente.
 *
 * O ESP8266 disponibiliza os dados em /dados.
 * A função atualizarPainel() atualiza a interface.
 */

function atualizarPainel(distancia, estado) {
  const elementoDistancia = document.getElementById("distancia");
  const elementoStatus = document.getElementById("status");
  const meterFill = document.getElementById("meterFill");

  if (!Number.isFinite(distancia) || distancia < 0) {
    elementoDistancia.textContent = "--";
    elementoStatus.textContent = "Aguardando dados";
    meterFill.style.width = "0%";
    return;
  }

  elementoDistancia.textContent = distancia.toFixed(1);
  elementoStatus.textContent = estado || "Sem classificação";

  // 30 cm = referência para início de atenção.
  // 15 cm = referência para alerta.
  const nivel = Math.max(0, Math.min(100, ((30 - distancia) / 15) * 100));
  meterFill.style.width = nivel + "%";
}

async function buscarDados() {
  try {
    const resposta = await fetch("/dados");

    if (!resposta.ok) {
      throw new Error("Não foi possível obter os dados.");
    }

    const dados = await resposta.json();

    atualizarPainel(
      Number(dados.distancia),
      dados.estado
    );
  } catch (erro) {
    console.error(erro);
    atualizarPainel(NaN, null);
    document.getElementById("status").textContent = "Sem conexão";
  }
}

// Atualiza o painel periodicamente.
buscarDados();
setInterval(buscarDados, 1000);
