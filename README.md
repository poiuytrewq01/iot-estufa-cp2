Monitoramento de Estufa Agrícola com IoT
Trabalho prático da disciplina de Internet das Coisas — 3º Semestre de Análise e Desenvolvimento de Sistemas — FIAP
Integrantes:

Artur Pioli — RM565597
Kevin Martins — RM563454
Pedro Claes — RM566058
Matheus Arazin — RM556649


Descrição do Projeto
A ideia do projeto surgiu pensando em como a tecnologia pode ajudar no agronegócio. Desenvolvemos um sistema de monitoramento de uma estufa agrícola usando IoT, onde sensores capturam temperatura e umidade do ambiente em tempo real e enviam essas informações para um dashboard online.
O ESP32 foi simulado no Wokwi com um sensor DHT22, que mede tanto temperatura quanto umidade. Os dados são enviados via protocolo MQTT para o broker HiveMQ e recebidos pelo Node-RED, que processa tudo e exibe num dashboard. As leituras ficam salvas no banco de dados Oracle da FIAP e o sistema também consome a API do OpenWeatherMap para mostrar o clima externo ao lado dos dados da estufa.

Arquitetura da Solução
ESP32 (Wokwi)
    |
    | MQTT (broker.hivemq.com)
    |
Node-RED
    |-- Dashboard (localhost:1880/ui)
    |-- Banco de Dados Oracle (oracle.fiap.com.br)
    |-- API OpenWeatherMap (clima externo)
O fluxo funciona assim:

O ESP32 lê o sensor DHT22 a cada 5 segundos
Publica os dados nos tópicos estufa1/temperatura e estufa1/umidade via MQTT
O Node-RED assina esses tópicos e recebe os dados automaticamente
Os valores aparecem nos gauges e gráficos do dashboard em tempo real
Se a temperatura passar de 35°C ou a umidade cair abaixo de 40%, um alerta é gerado
Todos os dados são salvos na tabela leituras no Oracle
A cada 10 minutos a API do OpenWeather atualiza os dados climáticos externos


Tecnologias Utilizadas
TecnologiaFunçãoESP32 + DHT22 (Wokwi)Simulação do microcontrolador e sensoresMQTTProtocolo de comunicação IoTHiveMQBroker MQTT públicoNode-REDProcessamento, automação e dashboardnode-red-dashboardInterface visual em tempo realnode-red-contrib-oracledb-modConexão com banco OracleOracle Database (FIAP)Armazenamento dos dadosOpenWeatherMap APIDados climáticos externos

Sensores Utilizados

DHT22 — sensor de temperatura (°C) e umidade relativa (%)
Conectado ao pino D4 do ESP32
Leitura a cada 5 segundos


Tópicos MQTT
TópicoDadoestufa1/temperaturaTemperatura em °Cestufa1/umidadeUmidade em %estufa1/alertaMensagens de alertaestufa1/statusStatus do dispositivo

Estrutura do Repositório
/
├── main.ino                  # Código do ESP32
├── diagram.json              # Circuito do Wokwi
├── libraries.txt             # Bibliotecas usadas no Wokwi
├── nodered_flow_final.json   # Fluxo do Node-RED
├── banco_dados_oracle.sql    # Script do banco de dados
└── README.md                 # Documentação

Instruções de Execução
1. Simulação no Wokwi

Acesse wokwi.com e crie um projeto ESP32
Cole o conteúdo de main.ino no editor
Substitua o diagram.json pelo arquivo do repositório
Adicione as bibliotecas do arquivo libraries.txt
Clique em Play para iniciar

2. Banco de Dados

Conecte no Oracle da FIAP pelo SQL Developer
Execute o script banco_dados_oracle.sql

3. Node-RED

Instale o Node.js e rode npm install -g node-red no terminal
Instale as paletas node-red-dashboard e node-red-contrib-oracledb-mod
Importe o arquivo nodered_flow_final.json
Configure a conexão Oracle com os dados da FIAP
Substitua a API Key do OpenWeather na URL do nó correspondente
Clique em Deploy
Acesse o dashboard em http://localhost:1880/ui

 Vídeo Demonstrativo
Assistir no YouTube
 Autores

Artur Pioli — RM565597
Kevin Martins — RM563454
Pedro Claes — RM566058
Matheus Arazin — RM556649

Projeto desenvolvido para a disciplina de Internet das Coisas (IoT) — FIAP.
