-- +migrate Up

CREATE TABLE "player"."iv_stats"
(
    "iv_id"      uuid NOT NULL,
    "hp"         integer NOT NULL,
    "attack"     integer NOT NULL,
    "defence"    integer NOT NULL,
    "speed"      integer NOT NULL,
    "sp_attack"  integer NOT NULL,
    "sp_defence" integer NOT NULL,
    CONSTRAINT "PK_stats" PRIMARY KEY ( "iv_id" )
);

-- +migrate Down
DROP TABLE "player"."iv_stats";