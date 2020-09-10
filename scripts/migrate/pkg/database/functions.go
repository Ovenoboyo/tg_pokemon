package database

import (
	"database/sql"
	"fmt"
	"github.com/Ovenoboyo/tg_pokemon/tree/pokemon/scripts/migrate/pkg/helpers"
	_ "github.com/lib/pq"
	"github.com/markbates/pkger"
	"github.com/rubenv/sql-migrate"
)

func GetConn() *sql.DB {

	conn, err := sql.Open("postgres", helpers.PgConnString)

	if err != nil {
		fmt.Println(err)
	}

	return conn
}

func RunMigrations() error {

	migrationsData := &migrate.HttpFileSystemMigrationSource{
		FileSystem: pkger.Dir("/pkg/database/migrations/pokemon"),
	}

	err := doMigrate(migrationsData)
	if err != nil {
		return err
	}

	return nil
}

func doMigrate(migrations *migrate.HttpFileSystemMigrationSource) error {
	conn := GetConn()

	n, err := migrate.Exec(conn, "postgres", migrations, migrate.Up)

	if err != nil {
		return err
	}

	err = conn.Close()
	if err != nil {
		return err
	}

	fmt.Printf("Applied %d migrations", n)
	return nil
}
