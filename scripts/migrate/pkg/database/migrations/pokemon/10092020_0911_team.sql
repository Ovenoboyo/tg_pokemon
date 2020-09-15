-- +migrate Up
CREATE TABLE "player"."team" (
    "team_id" varchar(20) NOT NULL,
    "pokemon_id_0" varchar(20) NOT NULL,
    "pokemon_id_1" varchar(20) NULL,
    "pokemon_id_2" varchar(20) NULL,
    "pokemon_id_3" varchar(20) NULL,
    "pokemon_id_4" varchar(20) NULL,
    "pokemon_id_5" varchar(20) NULL,
    CONSTRAINT "PK_team" PRIMARY KEY ("team_id"),
    CONSTRAINT "FK_101" FOREIGN KEY ("pokemon_id_3") REFERENCES "player"."user_pokemon" ("pokemon_id"),
    CONSTRAINT "FK_104" FOREIGN KEY ("pokemon_id_4") REFERENCES "player"."user_pokemon" ("pokemon_id"),
    CONSTRAINT "FK_107" FOREIGN KEY ("pokemon_id_5") REFERENCES "player"."user_pokemon" ("pokemon_id"),
    CONSTRAINT "FK_92" FOREIGN KEY ("pokemon_id_0") REFERENCES "player"."user_pokemon" ("pokemon_id"),
    CONSTRAINT "FK_95" FOREIGN KEY ("pokemon_id_1") REFERENCES "player"."user_pokemon" ("pokemon_id"),
    CONSTRAINT "FK_98" FOREIGN KEY ("pokemon_id_2") REFERENCES "player"."user_pokemon" ("pokemon_id")
);
CREATE INDEX "fkIdx_101" ON "player"."team" ("pokemon_id_3");
CREATE INDEX "fkIdx_104" ON "player"."team" ("pokemon_id_4");
CREATE INDEX "fkIdx_107" ON "player"."team" ("pokemon_id_5");
CREATE INDEX "fkIdx_92" ON "player"."team" ("pokemon_id_0");
CREATE INDEX "fkIdx_95" ON "player"."team" ("pokemon_id_1");
CREATE INDEX "fkIdx_98" ON "player"."team" ("pokemon_id_2");
-- +migrate Down
DROP TABLE IF EXISTS "player"."team";
DROP INDEX IF EXISTS "fkIdx_101";
DROP INDEX IF EXISTS "fkIdx_104";
DROP INDEX IF EXISTS "fkIdx_107";
DROP INDEX IF EXISTS "fkIdx_92";
DROP INDEX IF EXISTS "fkIdx_95";
DROP INDEX IF EXISTS "fkIdx_98";