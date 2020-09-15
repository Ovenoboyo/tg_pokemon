-- +migrate Up
CREATE TABLE "player"."player" (
    "player_id" varchar(128) NOT NULL,
    "team_id" varchar(20) NOT NULL,
    "name" varchar(128) NOT NULL,
    "gender" integer NOT NULL,
    "pkc" money NOT NULL,
    CONSTRAINT "PK_player" PRIMARY KEY ("player_id"),
    CONSTRAINT "FK_110" FOREIGN KEY ("team_id") REFERENCES "player"."team" ("team_id")
);
CREATE INDEX "fkIdx_110" ON "player"."player" ("team_id");
-- +migrate Down
DROP TABLE IF EXISTS "player"."player";
DROP INDEX IF EXISTS "fkIdx_110";