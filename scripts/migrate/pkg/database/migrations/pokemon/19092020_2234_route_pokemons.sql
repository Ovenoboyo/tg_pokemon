-- +migrate Up
CREATE TABLE "public"."route_pokemons"
(
 "generated_id" SERIAL,
 "route_no"     integer NOT NULL,
 "pokedex_no"   integer NOT NULL,
 "chance"       decimal NOT NULL,
 CONSTRAINT "PK_route_pokemons" PRIMARY KEY ( "generated_id" ),
 CONSTRAINT "FK_259" FOREIGN KEY ( "pokedex_no" ) REFERENCES "public"."pokemon" ( "pokedex_no" )
);

CREATE INDEX "fkIdx_259" ON "public"."route_pokemons"
(
 "pokedex_no"
);

-- +migrate Down
DROP INDEX IF EXISTS "fkIdx_259";
DROP TABLE IF EXISTS "public"."route_pokemons";
