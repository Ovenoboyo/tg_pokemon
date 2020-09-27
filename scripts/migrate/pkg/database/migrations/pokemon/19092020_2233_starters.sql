-- +migrate Up

CREATE TABLE "public"."starters"
(
 "generated_id" SERIAL,
 "pokedex_no"   integer NOT NULL,
 CONSTRAINT "PK_starters" PRIMARY KEY ( "generated_id" ),
 CONSTRAINT "FK_251" FOREIGN KEY ( "pokedex_no" ) REFERENCES "public"."pokemon" ( "pokedex_no" )
);

CREATE INDEX "fkIdx_251" ON "public"."starters"
(
 "pokedex_no"
);

-- +migrate Down
DROP INDEX IF EXISTS "fkIdx_251";
DROP TABLE IF EXISTS "public"."starters";
