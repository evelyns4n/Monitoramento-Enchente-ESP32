/*
 * Painel de monitoramento de enchente.
 *
 * A função atualizarPainel(distancia) concentra a atualização da interface.
 * Quando a comunicação com o ESP32 for validada, ela pode ser chamada com
 * o valor recebido pela rede.
 */

function atualizarPainel(distancia) {
  const elementoDistancia = document.getElementById("distancia");
  const elementoStatus = document.getElementById("status");
  const meterFill = document.getElementById("meterFill");

  if (!Number.isFinite(distancia)) {
    elementoDistancia.textContent = "--";
    elementoStatus.textContent = "Aguardando dados";
    meterFill.style.width = "0%";
    return;
  }

  elementoDistancia.textContent = distancia.toFixed(1);

  /*
   * Estes limites são provisórios.
   * A calibração final deve ser feita depois que o sensor e o ponto
   * de instalação forem confirmados.
   */
  const nivel = Math.max(0, Math.min(100, 100 - distancia));

  meterFill.style.width = nivel + "%";

  if (distancia > 60) {
    elementoStatus.textContent = "Normal";
  } else if (distancia > 30) {
    elementoStatus.textContent = "Atenção";
  } else {
    elementoStatus.textContent = "Alerta";
  }
}

// Estado inicial do painel.
atualizarPainel(NaN);
