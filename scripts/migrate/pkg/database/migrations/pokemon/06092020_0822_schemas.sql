-- +migrate Up
CREATE SCHEMA IF NOT EXISTS public;

CREATE SCHEMA IF NOT EXISTS player;

-- +migrate Down
DROP SCHEMA IF EXISTS player CASCADE;

