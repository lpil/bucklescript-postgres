# Bucklescript Postgres

A rough and ready low level and largely unsafe wrapper around the Javascript
`pg` Postgresql driver.

## Running the tests

```sh
createdb bucklescript-postgres
createuser -s bucklescript-postgres

npm run start # In one terminal
npm run test  # In another
```
