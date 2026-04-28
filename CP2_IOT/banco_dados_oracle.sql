-- ============================================================
--  Script de criação das tabelas - IoT Estufa
--  Conexão: oracle.fiap.com.br | SID: orcl | User: rm556649
--  Execute no SQL Developer com a conexão "fiap"
-- ============================================================

-- Tabela principal de leituras dos sensores
CREATE TABLE rm556649.leituras (
  id        NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
  sensor    VARCHAR2(50)   NOT NULL,
  valor     NUMBER(10,2)   NOT NULL,
  unidade   VARCHAR2(10)   NOT NULL,
  timestamp TIMESTAMP      DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- Tabela de alertas
CREATE TABLE rm556649.alertas (
  id        NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
  mensagem  VARCHAR2(500)  NOT NULL,
  timestamp TIMESTAMP      DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- Dados de exemplo para testar
INSERT INTO rm556649.leituras (sensor, valor, unidade) VALUES ('temperatura', 24.50, 'C');
INSERT INTO rm556649.leituras (sensor, valor, unidade) VALUES ('umidade',     68.00, '%');
INSERT INTO rm556649.leituras (sensor, valor, unidade) VALUES ('temperatura', 26.80, 'C');
INSERT INTO rm556649.leituras (sensor, valor, unidade) VALUES ('umidade',     63.00, '%');

COMMIT;

-- Verificar se funcionou:
SELECT * FROM rm556649.leituras;
