type pool;

type query = string;

type param;

type error;

[@bs.deriving abstract]
type fieldInfo = {
  name: string,
};

[@bs.deriving abstract]
type result = {
  rowCount: int,
  fields: array(fieldInfo),
  command: string,
  rows: array(Js.Json.t),
};

[@bs.deriving abstract]
type credentials = {
  max: int,
  host: string,
  user: string,
  password: string,
  database: string,
};

[@bs.new] [@bs.module "pg"] external makePool : credentials => pool = "Pool";

[@bs.send]
external execQuery : (pool, query, array(param)) => Js.Promise.t(result) =
  "query";

let query = (pool, ~params=[||], query) => execQuery(pool, query, params);

external int : int => param = "%identity";

external string : string => param = "%identity";
