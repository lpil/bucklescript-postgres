open Jest;

open Expect;

open Js.Promise;

let credentials =
  PgRaw.credentials(
    ~max=1,
    ~host="localhost",
    ~user="bucklescript-postgres",
    ~password="bucklescript-postgres",
    ~database="bucklescript-postgres",
  );

let pool = PgRaw.makePool(credentials);

beforeAllPromise(() =>
  {|
/* CREATE TABLE IF NOT EXISTS cats ( */
/*   id INTEGER PRIMARY KEY, */
/*   name VARCHAR(50) NOT NULL, */
/*   isCute boolean NOT NULL DEFAULT true */
/* ); */
|}
  |> PgRaw.query(pool)
);

let parseResult = result =>
  {
    "rowCount": PgRaw.rowCount(result),
    "fieldNames": PgRaw.fields(result) |> Array.map(PgRaw.name),
    "command": PgRaw.command(result),
    "rows": PgRaw.rows(result),
  }
  |> resolve;

testPromise("simple select without params", () => {
  let expected = {
    "rowCount": 1,
    "fieldNames": [|"?column?"|],
    "command": "SELECT",
    "rows": [|
      Js.Json.object_(
        Js.Dict.fromList([("?column?", Js.Json.number(1.))]),
      ),
    |],
  };
  "SELECT 1"
  |> PgRaw.query(pool)
  |> then_(parseResult)
  |> then_(result => expect(result) |> toEqual(expected) |> resolve);
});

testPromise("simple select with params", () => {
  let expected = {
    "rowCount": 1,
    "fieldNames": [|"?column?"|],
    "command": "SELECT",
    "rows": [|
      Js.Json.object_(
        Js.Dict.fromList([("?column?", Js.Json.number(7.))]),
      ),
    |],
  };
  "SELECT ($1::int + $2)"
  |> PgRaw.query(pool, ~params=PgRaw.([|int(1), int(6)|]))
  |> then_(parseResult)
  |> then_(result => expect(result) |> toEqual(expected) |> resolve);
});
