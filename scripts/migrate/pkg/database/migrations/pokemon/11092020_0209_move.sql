-- +migrate Up
CREATE TABLE "player"."move" (
    "move_id" varchar(20) NOT NULL,
    "name" varchar(50) NOT NULL,
    "element_type" integer NOT NULL,
    "damage" integer NOT NULL,
    "accuracy" integer NOT NULL,
    "max_pp" integer NOT NULL,
    CONSTRAINT "PK_moves" PRIMARY KEY ("move_id")
);
-- +migrate Down
DROP TABLE IF EXISTS "player"."move" CASCADE;