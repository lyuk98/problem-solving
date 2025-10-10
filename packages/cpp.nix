{
  lib,
  stdenv,

  pname,
  problemDir,
  source,

  version ? "0",
}:
let
  filenames = builtins.map (path: builtins.baseNameOf path) (lib.fileset.toList source);
in
stdenv.mkDerivation {
  inherit pname;
  inherit version;

  src = lib.fileset.toSource {
    root = problemDir;
    fileset = source;
  };

  buildPhase = ''
    g++ -o ${pname} -Wall -O2 -std=c++23 ${builtins.concatStringsSep " " filenames}
  '';

  installPhase = ''
    install --verbose -D ${pname} "$out/bin/${pname}"
  '';
}
