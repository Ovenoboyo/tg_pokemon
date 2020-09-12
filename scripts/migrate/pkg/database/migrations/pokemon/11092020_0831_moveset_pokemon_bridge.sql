-- +migrate Up
CREATE TABLE "moveset_pokemon_bridge" (
    "moveset_id" uuid NOT NULL,
    "generated_id" integer NOT NULL,
    "pokedex_no" integer NOT NULL,
    CONSTRAINT "PK_moveset_pokemon_bridge" PRIMARY KEY ("generated_id"),
    CONSTRAINT "FK_224" FOREIGN KEY ("moveset_id") REFERENCES "moveset" ("moveset_id"),
    CONSTRAINT "FK_227" FOREIGN KEY ("pokedex_no") REFERENCES "public"."pokemon" ("pokedex_no")
);
CREATE INDEX "fkIdx_224" ON "moveset_pokemon_bridge" ("moveset_id");
CREATE INDEX "fkIdx_227" ON "moveset_pokemon_bridge" ("pokedex_no");
-- +migrate Down
DROP TABLE IF EXISTS "moveset_pokemon_bridge";
DROP INDEX IF EXISTS "fkIdx_224";
DROP INDEX IF EXISTS "fkIdx_227";