-- +migrate Up

CREATE TABLE "player"."player_move_bridge"
(
 "generated_id" integer NOT NULL,
 "move_id"      VARCHAR(20) NOT NULL,
 "pokemon_id"   VARCHAR(20) NOT NULL,
 "position"     integer NOT NULL,
 CONSTRAINT "PK_player_move_bridge" PRIMARY KEY ( "generated_id" ),
 CONSTRAINT "FK_187" FOREIGN KEY ( "move_id" ) REFERENCES "player"."move" ( "move_id" ),
 CONSTRAINT "FK_191" FOREIGN KEY ( "pokemon_id" ) REFERENCES "player"."user_pokemon" ( "pokemon_id" )
);

CREATE INDEX "fkIdx_187" ON "player"."player_move_bridge"
(
 "move_id"
);

CREATE INDEX "fkIdx_191" ON "player"."player_move_bridge"
(
 "pokemon_id"
);

-- +migrate Down
DROP INDEX IF EXISTS "fkIdx_187";
DROP INDEX IF EXISTS "fkIdx_191";
DROP TABLE IF EXISTS "player"."player_move_bridge";