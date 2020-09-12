-- +migrate Up

CREATE TABLE "player"."ev_stats"
(
    "ev_id"      uuid NOT NULL,
    "hp"         integer NOT NULL,
    "attack"     integer NOT NULL,
    "defence"    integer NOT NULL,
    "speed"      integer NOT NULL,
    "sp_attack"  integer NOT NULL,
    "sp_defence" integer NOT NULL,
    CONSTRAINT "EV_stats" PRIMARY KEY ( "ev_id" )
);

CREATE TABLE "player"."iv_stats"
(
    "iv_id"      uuid NOT NULL,
    "hp"         integer NOT NULL,
    "attack"     integer NOT NULL,
    "defence"    integer NOT NULL,
    "speed"      integer NOT NULL,
    "sp_attack"  integer NOT NULL,
    "sp_defence" integer NOT NULL,
    CONSTRAINT "IV_stats" PRIMARY KEY ( "iv_id" )
);


CREATE TABLE "player"."user_pokemon"
(
    "pokemon_id" uuid NOT NULL,
    "pokedex_no" integer NOT NULL,
    "ev_id"      uuid NOT NULL,
    "iv_id"      uuid NOT NULL,
    "nickname"   varchar(50) NOT NULL,
    CONSTRAINT "PK_user_pokemon" PRIMARY KEY ( "pokemon_id" ),
    CONSTRAINT "FK_201" FOREIGN KEY ( "ev_id" ) REFERENCES "player"."ev_stats" ( "ev_id" ),
    CONSTRAINT "FK_204" FOREIGN KEY ( "iv_id" ) REFERENCES "player"."iv_stats" ( "iv_id" ),
    CONSTRAINT "FK_82" FOREIGN KEY ( "pokedex_no" ) REFERENCES "public"."pokemon" ( "pokedex_no" )
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
     "pokedex_no"
        );


-- +migrate Down

DROP TABLE IF EXISTS "player"."user_pokemon";
DROP INDEX IF EXISTS "fkIdx_201";
DROP INDEX IF EXISTS "fkIdx_204";
DROP INDEX IF EXISTS "fkIdx_82";
