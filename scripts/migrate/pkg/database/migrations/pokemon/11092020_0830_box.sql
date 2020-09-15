-- +migrate Up
CREATE TABLE "player"."box" (
    "box_id" varchar(20) NOT NULL,
    "pk_count" integer NOT NULL,
    CONSTRAINT "PK_box" PRIMARY KEY ("box_id")
);
-- +migrate Down
DROP TABLE IF EXISTS "player"."box";