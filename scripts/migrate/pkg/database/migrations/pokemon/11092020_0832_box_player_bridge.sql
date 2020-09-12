-- +migrate Up

CREATE TABLE "player"."box_player_bridge"
(
    "generated_id" integer NOT NULL,
    "box_id"       uuid NOT NULL,
    "player_id"    varchar(128) NOT NULL,
    CONSTRAINT "PK_box_player_bridge" PRIMARY KEY ( "generated_id" ),
    CONSTRAINT "FK_155" FOREIGN KEY ( "box_id" ) REFERENCES "player"."box" ( "box_id" ),
    CONSTRAINT "FK_158" FOREIGN KEY ( "player_id" ) REFERENCES "player"."player" ( "player_id" )
);

CREATE INDEX "fkIdx_155" ON "player"."box_player_bridge"
    (
     "box_id"
        );

CREATE INDEX "fkIdx_158" ON "player"."box_player_bridge"
    (
     "player_id"
        );

-- +migrate Down
DROP TABLE IF EXISTS "player"."box_player_bridge";
DROP INDEX IF EXISTS "fkIdx_155";
DROP INDEX IF EXISTS "fkIdx_158";