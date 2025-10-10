{
  lib,
  stdenv,
  jdk,
  jre,
  stripJavaArchivesHook,
  makeWrapper,

  pname,
  problemDir,
  source,

  version ? "0",
}:
let
  filenames = builtins.map (path: builtins.baseNameOf path) (lib.fileset.toList source);
  names = builtins.map (filename: lib.removeSuffix ".java" filename) filenames;
in
stdenv.mkDerivation {
  inherit pname;
  inherit version;

  src = lib.fileset.toSource {
    root = problemDir;
    fileset = source;
  };

  nativeBuildInputs = [
    jdk
    stripJavaArchivesHook
    makeWrapper
  ];

  buildPhase = ''
    runHook preBuild

    javac -verbose ${builtins.concatStringsSep " " filenames}
    jar --create --file ${pname}.jar --verbose *.class

    runHook postBuild
  '';

  installPhase = ''
    runHook preInstall

    install -D --mode 644 ${pname}.jar $out/share/java/${pname}.jar

    mkdir --parents $out/bin
    makeWrapper ${jre}/bin/java $out/bin/${pname} \
      --add-flags "-classpath $out/share/java/${pname}.jar ${builtins.elemAt names 0}"

    runHook postInstall
  '';
}
