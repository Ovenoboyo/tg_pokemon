-- +migrate Up
CREATE TABLE "evolve_moveset_pokemon_bridge" (
    "evolve_moveset_id" varchar(20) NOT NULL,
    "generated_id" integer NOT NULL,
    "pokedex_no" integer NOT NULL,
    CONSTRAINT "PK_moveset_pokemon_bridge" PRIMARY KEY ("generated_id"),
    CONSTRAINT "FK_224" FOREIGN KEY ("evolve_moveset_id") REFERENCES "evolve_moveset" ("evolve_moveset_id"),
    CONSTRAINT "FK_227" FOREIGN KEY ("pokedex_no") REFERENCES "public"."pokemon" ("pokedex_no")
);
CREATE INDEX "fkIdx_224" ON "evolve_moveset_pokemon_bridge" ("evolve_moveset_id");
CREATE INDEX "fkIdx_227" ON "evolve_moveset_pokemon_bridge" ("pokedex_no");
-- +migrate Down
DROP TABLE IF EXISTS "evolve_moveset_pokemon_bridge";
DROP INDEX IF EXISTS "fkIdx_224";
DROP INDEX IF EXISTS "fkIdx_227";