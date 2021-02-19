{ name = "record"
, dependencies =
  [ "functions"
  , "prelude"
  , "st"
  , "typelevel-prelude"
  , "unsafe-coerce"
  , "assert"
  ]
, packages = ../pure-c/package-sets/packages.dhall
, sources = [ "src/**/*.purs", "test/**/*.purs" ]
}
