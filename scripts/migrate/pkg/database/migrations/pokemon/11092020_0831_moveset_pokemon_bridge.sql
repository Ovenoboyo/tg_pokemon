-- +migrate Up

CREATE TABLE "moveset_pokemon_bridge"
(
    "moveset_id"   uuid NOT NULL,
    "generated_id" integer NOT NULL,
    "Pokedex_No"   integer NOT NULL,
    CONSTRAINT "PK_moveset_pokemon_bridge" PRIMARY KEY ( "generated_id" ),
    CONSTRAINT "FK_224" FOREIGN KEY ( "moveset_id" ) REFERENCES "moveset" ( "moveset_id" ),
    CONSTRAINT "FK_227" FOREIGN KEY ( "Pokedex_No" ) REFERENCES "public"."pokemon" ( "Pokedex_No" )
);

CREATE INDEX "fkIdx_224" ON "moveset_pokemon_bridge"
    (
     "moveset_id"
        );

CREATE INDEX "fkIdx_227" ON "moveset_pokemon_bridge"
    (
     "Pokedex_No"
        );

-- +migrate Down
DROP TABLE "moveset_pokemon_bridge";
DROP INDEX "fkIdx_224";
DROP INDEX "fkIdx_227";