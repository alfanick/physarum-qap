#!/usr/local/bin/gawk -f


BEGIN{
  FS="\\input{|}"
}{
  regex="(%*)(.*)\\input{(.*)}";
  if(match($0,regex,a)){
    file = a[3];
    if(a[1]==""){
      match(file,".tex",b);
      if(RLENGTH<0){
          system("./recursiveInput.awk "file".tex");
      }
      else{
          system("./recursiveInput.awk "file);
      }
    }

  }
  else{
    print $0
  }
}
