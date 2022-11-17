package initializer

import (
	"github.com/Ovenoboyo/tg_pokemon/scripts/migrate/pkg/database"
	"github.com/Ovenoboyo/tg_pokemon/scripts/migrate/pkg/helpers"
)

// Initialize the whole app
func Init() error {
	helpers.InitPaths()
	err := database.RunMigrations()
	if err != nil {
		return err
	}
	return err
}
