-- +migrate Up
CREATE TABLE "public"."base_stats" (
    "base_stats_id" varchar(36) NOT NULL,
    "hp" integer NOT NULL,
    "attack" integer NOT NULL,
    "defence" integer NOT NULL,
    "speed" integer NOT NULL,
    "sp_attack" integer NOT NULL,
    "sp_defence" integer NOT NULL,
    CONSTRAINT "PK_stats" PRIMARY KEY ("base_stats_id")
);
-- +migrate Down
DROP TABLE IF EXISTS "public"."base_stats";