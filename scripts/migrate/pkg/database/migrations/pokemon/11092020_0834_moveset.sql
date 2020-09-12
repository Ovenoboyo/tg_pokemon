-- +migrate Up

CREATE TABLE "moveset"
(
    "moveset_id" uuid NOT NULL,
    "move_id"    uuid NOT NULL,
    "level"      integer NOT NULL,
    CONSTRAINT "PK_moveset" PRIMARY KEY ( "moveset_id" ),
    CONSTRAINT "FK_216" FOREIGN KEY ( "move_id" ) REFERENCES "player"."move" ( "move_id" )
);

CREATE INDEX "fkIdx_216" ON "moveset"
    (
     "move_id"
        );

-- +migrate Down
DROP TABLE "moveset";
DROP INDEX "fkIdx_216";