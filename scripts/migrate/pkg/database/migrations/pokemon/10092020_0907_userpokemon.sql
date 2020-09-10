-- +migrate Up
CREATE TABLE "player"."user_pokemon"
(
    "pokemon_id" uuid NOT NULL,
    "Pokedex_No" integer NOT NULL,
    "ev_id"      uuid NOT NULL,
    "iv_id"      uuid NOT NULL,
    "nickname"   varchar(50) NOT NULL,
    CONSTRAINT "PK_user_pokemon" PRIMARY KEY ( "pokemon_id" ),
    CONSTRAINT "FK_201" FOREIGN KEY ( "ev_id" ) REFERENCES "player"."ev_stats" ( "ev_id" ),
    CONSTRAINT "FK_204" FOREIGN KEY ( "iv_id" ) REFERENCES "player"."iv_stats" ( "iv_id" ),
    CONSTRAINT "FK_82" FOREIGN KEY ( "Pokedex_No" ) REFERENCES "public"."pokemon" ( "Pokedex_No" )
);

CREATE INDEX "fkIdx_201" ON "player"."user_pokemon"
    (
     "ev_id"
        );

CREATE INDEX "fkIdx_204" ON "player"."user_pokemon"
    (
     "iv_id"
        );

CREATE INDEX "fkIdx_82" ON "player"."user_pokemon"
    (
     "Pokedex_No"
        );


-- +migrate DOWN
DROP TABLE "player"."user_pokemon";
DROP INDEX "fkIdx_201";
DROP INDEX "fkIdx_204";
DROP INDEX "fkIdx_82";
