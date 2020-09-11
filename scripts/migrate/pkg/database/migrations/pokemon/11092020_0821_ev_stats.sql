-- +migrate Up

CREATE TABLE "player"."ev_stats"
(
    "ev_id"      uuid NOT NULL,
    "hp"         integer NOT NULL,
    "attack"     integer NOT NULL,
    "defence"    integer NOT NULL,
    "speed"      integer NOT NULL,
    "sp_attack"  integer NOT NULL,
    "sp_defence" integer NOT NULL,
    CONSTRAINT "PK_stats" PRIMARY KEY ( "ev_id" )
);

-- +migrate Down
DROP TABLE "player"."ev_stats";