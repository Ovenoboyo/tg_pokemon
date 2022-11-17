-- +migrate Up

CREATE TABLE "public"."pokemon_move_bridge"
(
 "generated_id" SERIAL NOT NULL,
 "pokedex_no"   integer NOT NULL,
 "move_id"      SERIAL NOT NULL,
 "level"        integer NOT NULL,
 CONSTRAINT "PK_moveset_pokemon_bridge" PRIMARY KEY ( "generated_id" ),
 CONSTRAINT "FK_227" FOREIGN KEY ( "pokedex_no" ) REFERENCES "public"."pokemon" ( "pokedex_no" ),
 CONSTRAINT "FK_273" FOREIGN KEY ( "move_id" ) REFERENCES "public"."move" ( "move_id" )
);

CREATE INDEX "fkIdx_227" ON "public"."pokemon_move_bridge"
(
 "pokedex_no"
);

CREATE INDEX "fkIdx_273" ON "public"."pokemon_move_bridge"
(
 "move_id"
);

-- +migrate Down

DROP INDEX IF EXISTS "fkIdx_273";
DROP INDEX IF EXISTS "fkIdx_227";
DROP TABLE IF EXISTS "public"."pokemon_move_bridge";