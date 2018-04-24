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

let makePool : credentials => pool;

let query : (pool, ~params:array(param)=?, query) => Js.Promise.t(result);

let int : int => param;

let string : string => param;
