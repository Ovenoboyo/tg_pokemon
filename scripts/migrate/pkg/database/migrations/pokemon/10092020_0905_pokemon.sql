-- +migrate Up
CREATE TABLE "public"."element_types" (
    "element_type_id" varchar(20) NOT NULL,
    "element_0" integer NOT NULL,
    "element_1" integer NULL,
    CONSTRAINT "PK_element_types" PRIMARY KEY ("element_type_id")
);
CREATE TABLE "public"."pokemon" (
    "pokedex_no" integer NOT NULL,
    "gender" integer NOT NULL,
    "nature" integer NOT NULL,
    "icon_path" varchar(128) NOT NULL,
    "name" varchar(128) NOT NULL,
    "base_stats_id" varchar(20) NOT NULL,
    "evolve_level" integer NULL,
    "evolve_pokemon" integer NULL,
    "element_type_id" varchar(20) NOT NULL,
    CONSTRAINT "PK_pokemon" PRIMARY KEY ("pokedex_no"),
    CONSTRAINT "FK_115" FOREIGN KEY ("base_stats_id") REFERENCES "public"."base_stats" ("base_stats_id"),
    CONSTRAINT "FK_143" FOREIGN KEY ("evolve_pokemon") REFERENCES "public"."pokemon" ("pokedex_no"),
    CONSTRAINT "FK_168" FOREIGN KEY ("element_type_id") REFERENCES "public"."element_types" ("element_type_id")
);
CREATE INDEX "fkIdx_115" ON "public"."pokemon" ("base_stats_id");
CREATE INDEX "fkIdx_143" ON "public"."pokemon" ("evolve_pokemon");
CREATE INDEX "fkIdx_168" ON "public"."pokemon" ("element_type_id");
-- +migrate Down
DROP TABLE IF EXISTS "public"."pokemon";
DROP INDEX IF EXISTS "fkIdx_115";
DROP INDEX IF EXISTS "fkIdx_143";
DROP INDEX IF EXISTS "fkIdx_168";
DROP TABLE IF EXISTS "public"."element_types";