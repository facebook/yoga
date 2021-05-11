#!/bin/bash

create_gradle_properties() {
  KEYID=$1
  PASSWORD=$2
  GPG_KEY_CONTENTS=$3
  GPG_LOCATION=~/.gradle/release.gpg
  GRADLE_PROPERTIES_LOCATION=~/.gradle/gradle.properties

  mkdir -p ~/.gradle

  rm -f $GPG_LOCATION
  rm -f $GRADLE_PROPERTIES_LOCATION

  echo $GPG_KEY_CONTENTS | base64 -d > $GPG_LOCATION

  printf "signing.keyId=$KEYID\nsigning.password=$PASSWORD\nsigning.secretKeyRingFile=$GPG_LOCATION\n" >> $GRADLE_PROPERTIES_LOCATION
}

create_gradle_properties $ORG_GRADLE_PROJECT_SIGNINGKEYID $ORG_GRADLE_PROJECT_SIGNINGPASSWORD $GPG_KEY_CONTENTS
