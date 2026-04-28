# Monitoramento de Estufa Agrícola com IoT

Trabalho prático da disciplina de Internet das Coisas — 3º Semestre de Análise e Desenvolvimento de Sistemas — FIAP

**Integrantes:**
- Artur Pioli — RM565597
- Kevin Martins — RM563454
- Pedro Claes — RM566058
- Matheus Arazin — RM556649

---

## Descrição do Projeto

A ideia do projeto surgiu pensando em como a tecnologia pode ajudar no agronegócio. Desenvolvemos um sistema de monitoramento de uma estufa agrícola usando IoT, onde sensores capturam temperatura e umidade do ambiente em tempo real e enviam essas informações para um dashboard online.

O ESP32 foi simulado no Wokwi com um sensor DHT22, que mede tanto temperatura quanto umidade. Os dados são enviados via protocolo MQTT para o broker HiveMQ e recebidos pelo Node-RED, que processa tudo e exibe num dashboard. As leituras ficam salvas no banco de dados Oracle da FIAP e o sistema também consome a API do OpenWeatherMap para mostrar o clima externo ao lado dos dados da estufa.

---

## Arquitetura da Solução

```
ESP32 (Wokwi)
    |
    | MQTT (broker.hivemq.com)
    |
Node-RED
    |-- Dashboard (localhost:1880/ui)
    |-- Banco de Dados Oracle (oracle.fiap.com.br)
    |-- API OpenWeatherMap (clima externo)
```

O fluxo funciona assim:
1. O ESP32 lê o sensor DHT22 a cada 5 segundos
2. Publica os dados nos tópicos `estufa1/temperatura` e `estufa1/umidade` via MQTT
3. O Node-RED assina esses tópicos e recebe os dados automaticamente
4. Os valores aparecem nos gauges e gráficos do dashboard em tempo real
5. Se a temperatura passar de 35°C ou a umidade cair abaixo de 40%, um alerta é gerado
6. Todos os dados são salvos na tabela `leituras` no Oracle
7. A cada 10 minutos a API do OpenWeather atualiza os dados climáticos externos

---

## Tecnologias Utilizadas

| Tecnologia | Função |
|---|---|
| ESP32 + DHT22 (Wokwi) | Simulação do microcontrolador e sensores |
| MQTT | Protocolo de comunicação IoT |
| HiveMQ | Broker MQTT público |
| Node-RED | Processamento, automação e dashboard |
| node-red-dashboard | Interface visual em tempo real |
| node-red-contrib-oracledb-mod | Conexão com banco Oracle |
| Oracle Database (FIAP) | Armazenamento dos dados |
| OpenWeatherMap API | Dados climáticos externos |

---

## Sensores Utilizados

- **DHT22** — sensor de temperatura (°C) e umidade relativa (%)
- Conectado ao pino D4 do ESP32
- Leitura a cada 5 segundos

---

## Tópicos MQTT

| Tópico | Dado |
|---|---|
| `estufa1/temperatura` | Temperatura em °C |
| `estufa1/umidade` | Umidade em % |
| `estufa1/alerta` | Mensagens de alerta |
| `estufa1/status` | Status do dispositivo |

---

## Estrutura do Repositório

```
/
├── main.ino                  # Código do ESP32
├── diagram.json              # Circuito do Wokwi
├── libraries.txt             # Bibliotecas usadas no Wokwi
├── nodered_flow_final.json   # Fluxo do Node-RED
├── banco_dados_oracle.sql    # Script do banco de dados
└── README.md                 # Documentação
```

---

## Instruções de Execução

### 1. Simulação no Wokwi
1. Acesse [wokwi.com](https://wokwi.com) e crie um projeto ESP32
2. Cole o conteúdo de `main.ino` no editor
3. Substitua o `diagram.json` pelo arquivo do repositório
4. Adicione as bibliotecas do arquivo `libraries.txt`
5. Clique em **Play** para iniciar

### 2. Banco de Dados
1. Conecte no Oracle da FIAP pelo SQL Developer
2. Execute o script `banco_dados_oracle.sql`

### 3. Node-RED
1. Instale o Node.js e rode `npm install -g node-red` no terminal
2. Instale as paletas `node-red-dashboard` e `node-red-contrib-oracledb-mod`
3. Importe o arquivo `nodered_flow_final.json`
4. Configure a conexão Oracle com os dados da FIAP
5. Substitua a API Key do OpenWeather na URL do nó correspondente
6. Clique em **Deploy**
7. Acesse o dashboard em `http://localhost:1880/ui`
