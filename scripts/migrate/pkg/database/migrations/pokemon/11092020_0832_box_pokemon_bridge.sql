-- +migrate Up

CREATE TABLE "player"."box_pokemon_bridge"
(
    "generated_id" integer NOT NULL,
    "box_id"       uuid NOT NULL,
    "pokemon_id"   uuid NOT NULL,
    "position"     integer NOT NULL,
    CONSTRAINT "PK_box_pokemon_bridge" PRIMARY KEY ( "generated_id" ),
    CONSTRAINT "FK_137" FOREIGN KEY ( "box_id" ) REFERENCES "player"."box" ( "box_id" ),
    CONSTRAINT "FK_146" FOREIGN KEY ( "pokemon_id" ) REFERENCES "player"."user_pokemon" ( "pokemon_id" )
);

CREATE INDEX "fkIdx_137" ON "player"."box_pokemon_bridge"
    (
     "box_id"
        );

CREATE INDEX "fkIdx_146" ON "player"."box_pokemon_bridge"
    (
     "pokemon_id"
        );

-- +migrate Down
DROP TABLE IF EXISTS "player"."box_pokemon_bridge";
DROP INDEX IF EXISTS "fkIdx_137";
DROP INDEX IF EXISTS "fkIdx_146";