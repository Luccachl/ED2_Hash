class SistemaVotacao {
  constructor() {
    this.eleitores = new Set();
    this.votos = new Map();
  }

  votar(idEleitor, candidato) {
    if (this.eleitores.has(idEleitor)) {
      return "Erro: Eleitor ja votou.";
    }
    this.eleitores.add(idEleitor);
    if (!this.votos.has(candidato)) {
      this.votos.set(candidato, 0);
    }
    this.votos.set(candidato, this.votos.get(candidato) + 1);
    return `Voto registrado para ${candidato}!`;
  }

  exibirResultados() {
    if (this.votos.size === 0) {
      return "Nenhum voto registrado ainda.";
    }
    let resultados = "Resultado da eleicao:\n";
    for (const [candidato, totalVotos] of this.votos.entries()) {
      resultados += `${candidato}: ${totalVotos} votos\n`;
    }
    return resultados;
  }
}


const sistema = new SistemaVotacao();

console.log(sistema.votar("123", "Alice")); 
console.log(sistema.votar("123", "Bob"));  
console.log(sistema.votar("456", "Alice"));
console.log(sistema.votar("789", "Bob"));   
console.log(sistema.exibirResultados());    