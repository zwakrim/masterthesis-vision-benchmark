(function(){var window=this;var f=this,k=function(b){return"string"==typeof b},aa=/^[\w+/_-]+[=]{0,2}$/,n=null,p=function(){},r=function(b){var a=typeof b;if("object"==a)if(b){if(b instanceof Array)return"array";if(b instanceof Object)return a;var c=Object.prototype.toString.call(b);if("[object Window]"==c)return"object";if("[object Array]"==c||"number"==typeof b.length&&"undefined"!=typeof b.splice&&"undefined"!=typeof b.propertyIsEnumerable&&!b.propertyIsEnumerable("splice"))return"array";if("[object Function]"==c||"undefined"!=typeof b.call&&"undefined"!=typeof b.propertyIsEnumerable&&!b.propertyIsEnumerable("call"))return"function"}else return"null";else if("function"==a&&"undefined"==typeof b.call)return"object";return a};var u=function(b,a){if(k(b))return k(a)&&1==a.length?b.indexOf(a,0):-1;for(var c=0;c<b.length;c++)if(c in b&&b[c]===a)return c;return-1},ba=function(b,a){for(var c=b.length,e=k(b)?b.split(""):b,d=0;d<c;d++)d in e&&a.call(void 0,e[d],d,b)},ca=function(b){return Array.prototype.concat.apply([],arguments)};var v;a:{var x=f.navigator;if(x){var y=x.userAgent;if(y){v=y;break a}}v=""};var A=function(b){A[" "](b);return b};A[" "]=p;var B=function(){this.b="";this.v=da};B.prototype.l=!0;B.prototype.a=function(){return this.b};var C=function(b){return b instanceof B&&b.constructor===B&&b.v===da?b.b:"type_error:TrustedResourceUrl"},da={};var D=function(){this.g="";this.u=ea};D.prototype.l=!0;D.prototype.a=function(){return this.g};var fa=/^(?:(?:https?|mailto|ftp):|[^:/?#]*(?:[/?#]|$))/i,ea={},ha=function(b){var a=new D;a.g=b;return a};ha("about:blank");var ia=function(b,a){b.src=C(a);if(null===n){a:{if((a=f.document.querySelector("script[nonce]"))&&(a=a.nonce||a.getAttribute("nonce"))&&aa.test(a))break a;a=null}n=a||""}if(a=n)b.nonce=a};var ja=function(b){var a=!1,c;return function(){a||(c=b(),a=!0);return c}};var la=function(b){ka();var a=new B;a.b=b;return a},ka=p;var ma=/^[\w+/_-]+[=]{0,2}$/;var na=function(){if(!f.crypto)return Math.random();try{var b=new Uint32Array(1);f.crypto.getRandomValues(b);return b[0]/65536/65536}catch(a){return Math.random()}},oa=ja(function(){return-1!=v.indexOf("Google Web Preview")||1E-4>Math.random()}),pa=function(){try{a:{var b=f.document.querySelector("script[nonce]");if(b){var a=b.nonce||b.getAttribute("nonce");if(a&&ma.test(a)){var c=a;break a}}c=void 0}return c}catch(e){}};var E=function(){return f.googletag||(f.googletag={})};var F={1:"pagead2.googlesyndication.com",2:"pubads.g.doubleclick.net",3:"securepubads.g.doubleclick.net",173:"pubads.g.doubleclick.net",174:"securepubads.g.doubleclick.net",7:.02,13:1500,23:.001,24:200,27:.01,33:"pagead2.googlesyndication.com",37:.01,38:.001,47:0,53:"",58:1,65:.01,66:1E-5,67:0,68:0,69:1,71:.05,162:0,163:"",76:"",77:.001,78:0,81:.001,83:0,85:0,99:.01,103:.01,104:"/pagead/js/rum.js",113:1,114:1,115:0,116:0,117:1,118:1,124:1,208:.01,169:0,207:.01,127:0,129:.05,131:"",156:0,133:0,134:.01,135:.1,137:.01,167:1,138:"",143:.005,168:0,144:.001,187:.01,141:1,158:.001,150:".google.be",179:.05,170:!1,211:!1,183:0,196:.001,197:.001,152:[],172:null,175:"21061661,21061662,21061663,21061664,21061665,21061666,21061667,21061668,22316437,22316438",178:.05,182:1E3,188:0,189:.01,191:1512514930353,192:21510956201635,190:0xa781a7496a3,194:.95,225:.95,199:0,180:null,219:[],210:{},227:{},226:[],195:1,198:1,222:.05,223:.5,200:.95,201:0,202:"",203:.01,206:0,213:1,214:.05,215:.01,217:0,218:.01,220:!1,224:!0,228:"//www.googletagservices.com/pubconsole/"};F[6]=function(b,a){try{for(var c=null;c!=b;c=b,b=b.parent)switch(b.location.protocol){case "https:":return!0;case "file:":return!!a;case "http:":return!1}}catch(e){}return!0}(window);F[49]=(new Date).getTime();F[36]=/^true$/.test("false");F[46]=/^true$/.test("false");F[148]=/^true$/.test("false");F[221]=/^true$/.test("true");var G;a:{if(/^(-?[0-9.]{1,30})$/.test("{{MOD}}")){var qa=Number("{{MOD}}");if(!isNaN(qa)){G=qa;break a}}G=-1}F[204]=G;var H=function(){for(var b in F)this[b]=F[b]};H.b=void 0;H.a=function(){return H.b?H.b:H.b=new H};var I=function(b){return H.a()[b]},J=function(b,a){H.a()[b]=a},ra=E(),sa=H.a(),ta=ra._vars_,K;for(K in ta)sa[K]=ta[K];ra._vars_=sa;var ua=function(){return"200"},va=E();va.hasOwnProperty("getVersion")||(va.getVersion=ua);var wa=function(b,a,c){b.addEventListener?b.addEventListener(a,c,void 0):b.attachEvent&&b.attachEvent("on"+a,c)},xa=function(b,a,c){b.removeEventListener?b.removeEventListener(a,c,void 0):b.detachEvent&&b.detachEvent("on"+a,c)};var ya=function(b,a){var c=void 0===c?{}:c;this.error=b;this.context=a.context;this.line=a.line||-1;this.msg=a.message||"";this.file=a.file||"";this.id=a.id||"jserror";this.meta=c};var L=null;var za=function(b){var a=!1,c=!1;c=void 0===c?!1:c;a=void 0===a?!1:a;f.google_image_requests||(f.google_image_requests=[]);var e=f.document.createElement("img");if(a){var d=function(){if(a){var b=f.google_image_requests,c=u(b,e);0<=c&&Array.prototype.splice.call(b,c,1)}xa(e,"load",d);xa(e,"error",d)};wa(e,"load",d);wa(e,"error",d)}c&&(e.referrerPolicy="no-referrer");e.src=b;f.google_image_requests.push(e)};var Aa=ja(function(){var b=f.navigator&&f.navigator.userAgent||"";b=b.toLowerCase();return-1!=b.indexOf("firefox/")||-1!=b.indexOf("chrome/")||-1!=b.indexOf("opr/")}),M=function(b,a,c,e,d){e=void 0===e?"":e;var h=b.createElement("link");h.rel=c;-1!=c.toLowerCase().indexOf("stylesheet")?a=C(a):a instanceof B?a=C(a):a instanceof D?a=a instanceof D&&a.constructor===D&&a.u===ea?a.g:"type_error:SafeUrl":(a instanceof D||(a=a.l?a.a():String(a),fa.test(a)||(a="about:invalid#zClosurez"),a=ha(a)),a=a.a());h.href=a;e&&"preload"==c&&(h.as=e);d&&(h.nonce=d);if(b=b.getElementsByTagName("head")[0])try{b.appendChild(h)}catch(g){}};var Ba=/^\.google\.(com?\.)?[a-z]{2,3}$/,Ca=/\.(cn|com\.bi|do|sl|ba|by|ma)$/,N=function(b){return Ba.test(b)&&!Ca.test(b)},Da=function(b){return b.replace(/[\W]/g,function(b){return"&#"+b.charCodeAt()+";"})},O=f,Ea=function(b,a){b="https://"+("adservice"+a+"/adsid/integrator."+b);a=["domain="+encodeURIComponent(f.location.hostname)];P[3]>=+new Date&&a.push("adsid="+encodeURIComponent(P[1]));return b+"?"+a.join("&")},P,Q,R=function(){O=f;P=O.googleToken=O.googleToken||{};var b=+new Date;P[1]&&P[3]>b&&0<P[2]||(P[1]="",P[2]=-1,P[3]=-1,P[4]="",P[6]="");Q=O.googleIMState=O.googleIMState||{};N(Q[1])||(Q[1]=".google.com");"array"==r(Q[5])||(Q[5]=[]);"boolean"==typeof Q[6]||(Q[6]=!1);"array"==r(Q[7])||(Q[7]=[]);"number"==typeof Q[8]||(Q[8]=0)},Fa=function(b){try{b()}catch(a){f.setTimeout(function(){throw a;},0)}},Ha=function(b){"complete"==f.document.readyState||"loaded"==f.document.readyState||f.document.currentScript&&f.document.currentScript.async?Ga(3):b()},Ia=0,S={c:function(){return 0<Q[8]},h:function(){Q[8]++},m:function(){0<Q[8]&&Q[8]--},o:function(){Q[8]=0},f:function(){},s:function(){return!1},j:function(){return Q[5]},i:Fa},T={c:function(){return Q[6]},h:function(){Q[6]=!0},m:function(){Q[6]=!1},o:function(){Q[6]=!1},f:function(){},s:function(){return".google.com"!=Q[1]&&2<++Ia},j:function(){return Q[7]},i:function(b){Ha(function(){Fa(b)})}},Ga=function(b){1E-5>Math.random()&&za("https://pagead2.googlesyndication.com/pagead/gen_204?id=imerr&err="+b)};S.f=function(){if(!S.c()){var b=f.document,a=function(a){var c=Ea("js",a),d=pa();M(b,c,"preload","script",d);a=b.createElement("script");a.type="text/javascript";d&&(a.nonce=d);a.onerror=function(){return f.processGoogleToken({},2)};c=la(c);ia(a,c);try{(b.head||b.body||b.documentElement).appendChild(a),S.h()}catch(m){}},c=Q[1];a(c);".google.com"!=c&&a(".google.com");a={};var e=(a.newToken="FBT",a);f.setTimeout(function(){return f.processGoogleToken(e,1)},1E3)}};T.f=function(){if(!T.c()){var b=f.document,a=Ea("sync.js",Q[1]);M(b,a,"preload","script");a=Da(a);var c=A("script"),e="",d=pa();d&&(e='nonce="'+Da(d)+'"');var h="<"+c+' src="'+a+'" '+e+"></"+c+">"+("<"+c+" "+e+'>processGoogleTokenSync({"newToken":"FBS"},5);</'+c+">");Ha(function(){b.write(h);T.h()})}};var Ja=function(b){R();P[3]>=+new Date&&P[2]>=+new Date||b.f()},La=function(){f.processGoogleToken=f.processGoogleToken||function(b,a){return Ka(S,b,a)};Ja(S)},Ma=function(){f.processGoogleTokenSync=f.processGoogleTokenSync||function(b,a){return Ka(T,b,a)};Ja(T)},Ka=function(b,a,c){a=void 0===a?{}:a;c=void 0===c?0:c;var e=a.newToken||"",d="NT"==e,h=parseInt(a.freshLifetimeSecs||"",10),g=parseInt(a.validLifetimeSecs||"",10),m=a["1p_jar"]||"";a=a.pucrd||"";R();1==c?b.o():b.m();if(!e&&b.s())N(".google.com")&&(Q[1]=".google.com"),b.f();else{var q=O.googleToken=O.googleToken||{},l=0==c&&e&&k(e)&&!d&&"number"==typeof h&&0<h&&"number"==typeof g&&0<g&&k(m);d=d&&!b.c()&&(!(P[3]>=+new Date)||"NT"==P[1]);var t=!(P[3]>=+new Date)&&0!=c;if(l||d||t)d=+new Date,h=d+1E3*h,g=d+1E3*g,Ga(c),q[5]=c,q[1]=e,q[2]=h,q[3]=g,q[4]=m,q[6]=a,R();if(l||!b.c()){c=b.j();for(e=0;e<c.length;e++)b.i(c[e]);c.length=0}}};var Na=function(){this.a=null},Oa=function(b,a){b.a=a};Na.prototype.b=function(b,a,c,e,d){if(Math.random()>(void 0===c?.01:c))return!1;a.error&&a.meta&&a.id||(a=new ya(a,{context:b,id:void 0===d?"gpt_exception":d}));if(e||this.a)a.meta={},this.a&&this.a(a.meta),e&&e(a.meta);f.google_js_errors=f.google_js_errors||[];f.google_js_errors.push(a);f.error_rep_loaded||(a=f.document,b=a.createElement("script"),ia(b,la(f.location.protocol+"//pagead2.googlesyndication.com/pagead/js/err_rep.js")),(a=a.getElementsByTagName("script")[0])&&a.parentNode&&a.parentNode.insertBefore(b,a),f.error_rep_loaded=!0);return!1};var Pa=function(b,a){var c=void 0===c?b.b:c;try{a()}catch(e){if(!c.call(b,420,e,.01,void 0,"gpt_exception"))throw e;}};var Qa=function(b){if(!b.google_ltobserver){var a=new b.PerformanceObserver(function(a){var c=b.google_lt_queue=b.google_lt_queue||[];ba(a.getEntries(),function(b){return c.push(b)})});a.observe({entryTypes:["longtask"]});b.google_ltobserver=a}};var Ra=["21061818","21061819","21061820"],Sa=["21060622"],Ta=["21061212","21061213","21061214","21061277"];var Ua=[[null,null,2,[null,null,"1-0-23"]],[7,null,null,[1]]];var Va={3:[[50,[[21061799],[21061800],[21061801]]],[50,[[21061763],[21061764,[[5,null,null,[1]],[4,null,null,[1]]]]]],[10,[[21060132],[21060133,[[2,null,null,[1]]]]]],[1,[[22321847],[22322161,[[null,null,null,[null,null,null,["250","250"]],null,2]]],[22321848,[[null,null,null,[null,null,null,"50 50 50 50 50 50 50 50 50 50".split(" ")],null,2]]]]],[null,[[21061902],[21061901],[21061900]]],[100,[[21061811],[21061812,[[3,null,null,[1]]]]]],[500,[[21061845],[21061846,[[9,null,null,[1]]]]],[4,null,2]],[null,[[21061929,[[null,null,2,[null,null,"1-0-23"]]]],[21061928,[[null,null,null,[null,null,null,["v","1-0-23"]],null,1]]]]],[10,[[21061870],[21061871,[[4,null,null,[1]]]]]],[1E3,[[22316437,null,[2,[[8,null,null,1,null,-1],[7,null,null,1,null,5]]]],[22316438,null,[2,[[8,null,null,1,null,4],[7,null,null,1,null,10]]]]]],[10,[[21061803],[21061804]]]]};A("partner.googleadservices.com");var U=A("www.googletagservices.com"),V=!1,W=!1,X="",Y="",Wa=I(46)&&!I(6);X=Wa?"http:":"https:";Y=I(Wa?2:3);var Z=function(b,a){if(null===L){L="";try{var c="";try{c=f.top.location.hash}catch(d){c=f.location.hash}if(c){var e=c.match(/\bdeid=([\d,]+)/);L=e?e[1]:""}}catch(d){}}if(c=(c=L)&&c.match(new RegExp("\\b("+b.join("|")+")\\b")))b=c[0];else if(a)a:{a=b.length*a;if(!oa()&&(c=Math.random(),c<a)){c=na();b=b[Math.floor(c*b.length)];break a}b=null}else b=null;return b};(function(b){var a=new Na;Oa(a,function(b){b.methodId=420});Pa(a,function(){var a=b,e=E(),d=e.fifWin||window;a=a||d.document;var h=[],g=E();g.hasOwnProperty("cmd")||(g.cmd=h);if(e.evalScripts)e.evalScripts();else{(h=Z(Ta,I(178)))&&I(152).push(h);switch(h){case "21061213":W=!0;break;case "21061214":V=!0;break;case "21061277":V=W=!0}h=I(138)||Z(Sa,0)||Z(Ra,I(137))||Z(["21061149"],I(167));g=a;var m=Z(["21061590","21061591"],.001);I(219).length||J(219,Ua);a:{var q=I(210);for(l in q)if(Object.prototype.hasOwnProperty.call(q,l)){var l=!1;break a}l=!0}l&&J(210,Va);m&&("21061591"==m?(J(173,U),J(174,U)):J(163,m),I(152).push(m));-1!=v.indexOf("Mobile")||J(194,I(225));if(l=I(150))R(),N(l)&&(Q[1]=l);h&&I(152).push(h);if(!(l=g.currentScript))a:{if(g=g.scripts)for(l=0;l<g.length;l++)if(m=g[l],-1<m.src.indexOf(U+"/tag/js/gpt")){l=m;break a}l=null}J(172,l);d.PerformanceObserver&&d.PerformanceLongTaskTiming&&Qa(d);g=d;g=void 0===g?f:g;if(g=(g=g.performance)&&g.now?g.now():null)g={label:"1",type:9,value:g},d=d.google_js_reporting_queue=d.google_js_reporting_queue||[],1024>d.length&&d.push(g);if(d=I(76))var t=d;else{l=["199","200"];d=l[0]||"200";g="";if(I(131))t="200";else if(1<l.length){m=["21062007","21062008"];var w=[""];if(1>=w.length||m.length!=w.length)w=[];if(q=Z(ca(m,w),.001)){J(53,q);var z=0<=u(w,q);J(170,z);z&&(m=w);w=m[0];if(q!=w)for(z=1;z<m.length;++z)if(q==m[z]){t=l[z];break}if(q==w||parseInt(t,10)<parseInt(d,10))l=l[m.length-1],g="?v="+l,J(163,l)}}d=X+"//"+Y+"/gpt/pubads_impl_"+(t||d)+".js"+g;J(76,d);t=d}d=a.currentScript;if(!("complete"==a.readyState||"loaded"==a.readyState||d&&d.async)){d="gpt-impl-"+Math.random();try{g='<script id="'+d+'" src="'+t+'">\x3c/script>',V&&Aa()&&(g+='<link rel="preconnect" href="'+X+"//"+Y+'">'),a.write(g)}catch(Xa){}a.getElementById(d)&&(e._loadStarted_=!0,J(220,!1),"21061818"!=h&&"21060622"!=h&&"21061149"!=h||Ma())}e._loadStarted_||("21061818"!=h&&"21060622"!=h&&"21061149"!=h||La(),W&&M(a,t,"preload","script"),h=a.createElement("script"),h.src=t,h.async=!0,(a.head||a.body||a.documentElement).appendChild(h),V&&Aa()&&M(a,X+"//"+Y,"preconnect"),J(220,!0),e._loadStarted_=!0)}})})();}).call(this.googletag&&googletag.fifWin?googletag.fifWin.parent:this)
