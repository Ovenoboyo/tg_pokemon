package helpers

import (
	"fmt"
	"os"
)

var (
	PgConnString string
)
func InitPaths() {
	PgConnString = fmt.Sprintf("port=%s host=%s user=%s password=%s dbname=%s sslmode=disable", os.Getenv("hostport"), os.Getenv("hostname"), os.Getenv("username"), os.Getenv("password"), os.Getenv("databasename"))
	fmt.Println(PgConnString)
}