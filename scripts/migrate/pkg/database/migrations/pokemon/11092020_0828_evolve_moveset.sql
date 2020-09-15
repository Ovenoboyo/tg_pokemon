-- +migrate Up
CREATE TABLE "evolve_moveset" (
    "evolve_moveset_id" varchar(20) NOT NULL,
    "move_id" varchar(20) NOT NULL,
    "level" integer NOT NULL,
    CONSTRAINT "PK_evolve_moveset" PRIMARY KEY ("evolve_moveset_id"),
    CONSTRAINT "FK_216" FOREIGN KEY ("move_id") REFERENCES "player"."move" ("move_id")
);
CREATE INDEX "fkIdx_216" ON "evolve_moveset" ("move_id");
-- +migrate Down
DROP TABLE IF EXISTS "evolve_moveset";
DROP INDEX IF EXISTS "fkIdx_216";