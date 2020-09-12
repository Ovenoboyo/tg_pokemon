-- +migrate Up
CREATE SCHEMA IF NOT EXISTS public AUTHORIZATION pokemon_admin;
CREATE SCHEMA IF NOT EXISTS player AUTHORIZATION pokemon_admin;

-- +migrate Down
DROP SCHEMA player;