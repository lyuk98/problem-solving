{
  lib,
  stdenv,
  rustc,

  pname,
  problemDir,
  source,

  version ? "0",
}:
stdenv.mkDerivation {
  inherit pname;
  inherit version;

  src = lib.fileset.toSource {
    root = problemDir;
    fileset = source;
  };

  nativeBuildInputs = [
    rustc
  ];

  # rustc only accepts one file for compilation, so take the first file among the fileset
  buildPhase = ''
    rustc --edition 2024 -O -o ${pname} ${builtins.baseNameOf (builtins.elemAt (lib.fileset.toList source) 0)}
  '';

  installPhase = ''
    install --verbose -D ${pname} "$out/bin/${pname}"
  '';
}
