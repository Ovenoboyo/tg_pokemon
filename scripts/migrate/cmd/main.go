package main

import (
	"github.com/Ovenoboyo/tg_pokemon/tree/pokemon/scripts/migrate/pkg/helpers/initializer"
)

func main() {

	err := initializer.Init()
	if err != nil {
		panic(err)
	}
}
