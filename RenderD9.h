#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p)=NULL; } }

#define D3D_COLOR_LIME(a)	D3DCOLOR_ARGB(a, 204, 255, 153)
#define D3D_COLOR_WHITE(a)	D3DCOLOR_ARGB(a, 255, 255, 255)
#define D3D_COLOR_BLACK(a)	D3DCOLOR_ARGB(a, 0, 0, 0)
#define D3D_COLOR_RED(a)	D3DCOLOR_ARGB(a, 255, 0, 0)
#define D3D_COLOR_DARKRED(a)D3DCOLOR_ARGB(a, 153, 0, 0)
#define D3D_COLOR_GREEN(a)	D3DCOLOR_ARGB(a, 0, 255, 0)
#define D3D_COLOR_DARKGREEN(a)	D3DCOLOR_ARGB(a, 0, 153, 0)
#define D3D_COLOR_BLUE(a)	D3DCOLOR_ARGB(a, 0, 0, 255)
#define D3D_COLOR_DARKBLUE(a)D3DCOLOR_ARGB(a, 0, 0, 153)
#define D3D_COLOR_YELLOW(a)	D3DCOLOR_ARGB(a, 255, 255, 0)
#define D3D_COLOR_PINK(a)	D3DCOLOR_ARGB(a, 255, 0, 255)
#define D3D_COLOR_ORANGE(a)	D3DCOLOR_ARGB(a, 255, 153, 0)
#define D3D_COLOR_LIGHTBLUE(a)D3DCOLOR_ARGB(a, 0, 255, 255) 
#define D3D_COLOR_BROWN(a)	D3DCOLOR_ARGB(a, 153, 102, 0)
#define D3D_COLOR_GRAY(a)	D3DCOLOR_ARGB(a, 153, 153, 153)
#define D3D_COLOR_DARKGRAY(a)	D3DCOLOR_ARGB(a, 13, 13, 13)

struct D3DTLVERTEX
{
	float x, y, z, rhw;
	DWORD color;
};

class Render
{
	bool locked;
	bool resourcesCreated;

	LPD3DXLINE line;

public:
	bool setupComplete;

	LPDIRECT3DDEVICE9 pDevice;
	D3DVIEWPORT9 viewPort;
	HWND window;
	POINT mouse;
	LPD3DXFONT fntVerdana12;
	LPD3DXFONT fntVerdana11;
	LPD3DXFONT fntVerdana10;
	LPD3DXFONT fntVerdana9;
	LPD3DXFONT fntWeaponIcon;

	Render();
	~Render();
	void Setup(LPDIRECT3DDEVICE9 pDevice);
	void OnLostDevice();
	void OnResetDevice();
	void Present(LPDIRECT3DDEVICE9 pDevice);


	// Misc
	void SetFont(LPD3DXFONT font);
	

	// Rendering
	bool WorldToScreen(Vector vOrigin, Vector &vScreen);
	void DrawLine(float x1, float y1, float x2, float y2, float size, bool antiAlias, D3DCOLOR COLOR);
	void DrawLineFast(float x1, float y1, float x2, float y2, D3DCOLOR COLOR);
	void DrawString(float x, float y, D3DCOLOR color, char *format, ...);
	void DrawStringW(float x, float y, D3DCOLOR color, WCHAR *format, ...);
	void DrawStringWithFont(LPD3DXFONT fnt, float x, float y, D3DCOLOR color, char *format, ...);
	void DrawStringWithFontW(LPD3DXFONT fnt, float x, float y, D3DCOLOR color, wchar_t *format, ...);
	void DrawCircle(float x, float y, int radius, int numSides, float size, D3DCOLOR color);
	void DrawCircleFast(float x, float y, int radius, int numSides, D3DCOLOR color);
	void DrawFilledCircleFast(float x, float y, int radius, int numSides, D3DCOLOR color);
	void DrawBox(float x, float y, float height, float width, float size, D3DCOLOR COLOR);
	void DrawBoxFast(float x, float y, float height, float width, D3DCOLOR COLOR);
	void DrawBoxFastAlpha(float x, float y, float height, float width, D3DCOLOR COLOR, float alpha);
	void DrawCornierBoxFastAlpha(float x, float y, float height, float width, D3DCOLOR COLOR, float alpha);
	void DrawFilledRectangle(float x, float y, float height, float width, D3DCOLOR COLOR);
	void TexturedPolygon(int n, std::vector<FontVertex_tForCrosshair> vertice);
	float GetTextWitdh(char *text, LPD3DXFONT fnt);
	int GetTextWitdhW(wchar_t *text, LPD3DXFONT fnt);
	int FrameRate();
	void TexturedPolygon(int n, std::vector<FontVertex_tForCrosshair> vertice, CColor color);
	void DrawFilledCircle1(Vector2D center, CColor color, float radius, float points);
	
};
extern Render *render;
extern ImFont* GlobalFont;



static const char Pharamcy[41585 + 1] =
"7])#######LJhCC'/###I),##e3UhLXnH##JRdL<3WcS+GKQ%b?6e$$hExF>)f[%#IfMxb5=Kk0'HJf=+VgsVHYqr$;nh'#H^n42KBh+FY,>>#dC)m0l%lj;C@LhEoe68%LjE[$6PV=B"
"0[mD0&c08.(Y,11n1XGHWB:n#+f@J1^V+41,Jk7D7(88U0S`i0U$761(a(*HUYI%#BA6`a3)-p/+-0%J'>'Skt=4@6$$+GM0>K0FQ5[si_<jl&&B$)*T.d<BBjuhM02RA-BHU[-TT$=("
")$KI$m8nA#usJw5<_[FH1T*muu7YY#N>uu#K'2eGoFQs6$x)P]fTi$$M4JuBh12,_xfHo[aVus/`K[^I[(Fx#efG<-dYLp0+>00FWDlS'&GAi^(]u<%3$S+H`41*==1U(ajYJ_#mcFVC"
"L^2&:v[%/1VRqw-OnRfLXhH>#7%60I9he<65-Xx#oZ@U.kFnTVZLRm/[l/.vLuZg#WEi9../5##uCbA#v3A<@FjNS.Er=]O?4D8J<njk+sli(t.`J)tIL//(:=Fk4rLQn*&/JfLpW>Vd"
"?qUB#s/7crt1_V$?oKJ`ct&$.6+BGM.iU%kP:c@t21Y&#8VMq2SM:;$SSh7[3-$j:9%bh#TW=gG,Qj)##8uY#I;AwThAL&#C60L,Cl.l#0l1T.F8P>#1p8gLtwSfL'ApV-q.Dk=:Nk-$"
"?^k-$;Rn-$=&QF%@$0F%Gwn-$i0oiLJ50ZH-rH8%KV>8J2OpfD;F5F%U0f_/e,B>#_HwNF<_R:v^wx9)*tj-$13k-$+wj-$Cl+^#vRkA#f/dW-RX'UMK&=]OJ&a&#4m;R*]Ruk+5dPF%"
"O7pA#4N>HMtRGgL-+.7vm0trLvhJ+MB12X-*rQ-Hcso-$&cV-Hk5p-$'GI_&vVp-$?v+F.3jaCsYdDB#uqU:v)qbw'BrC>#@gX-H0/f-6$dp-$X`P:vW*LS-,M#<-xW_@-bM#<-geF?-"
"s>pV-)`PEnF,PY#JfG<-s&l?-7p-A-*cDE-'5fu-`pE?M)5T;--fF?-h@;=-,m7^.F=G##ChG<-t))t-%cv&M(^d)Mr7lc-s+D_&;P72'7Ui9;[ruu#0uNk41dC_&VVm92qPq92oqD_/"
"npK_&>5C_/^On%=8wv^]2O.F.J5w9)M<MuY%`Zw0#cW9V$l9B#t@1;$7q.>-56T;-6X`=-U6T;-kdQX.F.>>#SKwA-f)m<-v5`T.F>uu#1W_@-(hG<-eaDE-q=8F-]hG<-EbDE-90;.M"
"?>p)vhInqL04JqL9kFrLZV>W-G`Sk+4tU_AI?0F%?_n-$01n-$QO@;$D2B>#[di--2*_w'Y`m92GQG_&NhJ_&H;-F%*VxS][rMA4?&-g)#Fm%lpE8>dP#EHEilT;$3^+J_5lu(biw:&l"
"V6FG2RWaJ2N6YMC<%ZcaVs,8f]xr+s0Udv$uSj@tLq,AupImM(fAWVR$c'^#auwjk%A4gL*L>gL?RGgLtx)$#(XD78TF'L5_TQD*LNGnp^&vx4V@t(Nma:fq4UA2'JM#sIM$H]u1EK/)"
"B=r;-HO#<-:Z`=-&&kB-IN#<-<6T;-CZlS.p-QV#,r8gLTM1`jF$hMhOuUVH;.t-$[Bf_/5X/F%7/Vk=84_k+*qSMLC@.W-Vp4F%c&uVfPkiV$):Z;%4Pk#$aX?,;^dS2(/%(^#K.,^#"
"<F5F%UubGMRocW-lV+F.O;###la&_SWNmA#b=^;-jD(h.15YY#?@;=-f?2.0gD(v#x>uu#ctJ0%$a/?I(PuCj`$W9`]uuERKYXpT8d1l-K9n0#nIDI$hDit89F5D#<wYD#xq3R/5+il8"
",eEc4f.R#6aBAlLF/[]4nDk-$QP51M8V5s-AF4OM&'b$PxM5OMFI4;.FBru5p;nA#-ulhL?X`=-04:pMdDH>#owlhLekmhM#E55O1&KgL2X*+.rA,LM),UE#15L0Yq_]L;-`8I$s+)'6"
"O-P*Ikp]e404(B#GL@lLmE_%6f<9_SV+U$9_q80uuOkA#7I;62(a*`s3oZS%(25uu3(78%,[i8&^#Ke$-9^e$aCno%.C82'`)Ke$_[NP&/'4m'4<b2(hfC_&dw/2'8ggj(.8T=ukP^e$"
"i<gi'=&?g)f;Ke$8Z^e$nWGJ(Ffrd*1;9xtOp(,):5`D+?J7a+p(D_&w5`c)=P[A,H4k^,4>t[tYP@D*Bxj>-nSKe$C&_e$+mw%+QtG<.7AX@tc.X]+EC5s.JXc8/x@D_&4J9>,H_1p/"
"SB@60:D=%tmepu,M0@m0vlKe$NG_e$>+QV-V^<j1xrKe$FC28.KnEG2Ug8g2*YD_&G_io.Sm]G3X,5d3,`D_&R$JP/PK>A4(/Le$Yi_e$Q?+20blhA5*5Le$]r_e$]Zbi0U)7;6,;Le$"
"ZsBJ1_%3v6d:a;74xD_&f8$,2YSjo70GLe$e4`e$eSZc2m$>p82MLe$h=`e$po;D3_1ci94SLe$n1s%4j3_M:oH6j:<:E_&sLS]4ss;K;N]E+rOU`e$xh4>5x2jG<:fLe$s_`e$'.lu5"
"+sFE=Q`*fq_ELV6uA4&>$WbA>DRE_&0b-87x]0#?-A?\?\?TceIqi&eo7'/?v?B(Me$(+ae$:BEP80];s@D.Me$BZ&29sSDPA/f7pALkE_&Cv]i9-l[PB8OkmBZi.ip&;>J:2=kMCJ@Me$"
"3Lae$MVu+;;kgJDLFMe$UoUc;&]p(E:tcGET-F_&V47D<8$2)F=9`DFV3F_&bOn%=+:ixFRXMe$>nae$akN]=F#=#HT_Me$Awae$l00>>0narHVeMe$jHgu>C2^VIHG5sI_KF_&odGV?"
"Lr:TJi%nOo)9be$t))8@Q1iPK]wMe$LBbe$)E`o@9v6JL_'Ne$'^@PAN@3/MSUaJMgdF_&,#x1BW*g,No+7on4Zbe$1>XiB]?>)Oe9Ne$Wdbe$6Y9JCf)r&Pr.rRnnqp+DYN_]P_d6#Q"
"o&G_&?7QcD]jZYQhMjvQu1V7nxQ2DEb;jVRmQNe$c/ce$Ini%FkifSSoWNe$Q0J]FMBo1TjrbPTw>G_&RK+>Ghx02Us[?NU%8vUm5gbuGmI?/VujNe$nPce$],CVHvw;,WwpNe$eD$8I"
"VJD`Wu*8)X)WG_&f`ZoIs0]`XxE4&Y+^G_&q%<PJ[(=YY'-Oe$#sce$p@s1K+0hYZ)3Oe$&&de$%]SiKa[5S[+9Oe$#u4JL(?28]-T`S]3vG_&(:l+M1)f5^3J_=ld=de$-ULcM6>=2_"
"1KOe$1Gde$2q-DN?(q/`6MCxkj2e%O3M^f`8c5,a;8H_&;NE]O<7;da9P(]ko_de$@j&>PALi`b9dOe$<ide$E/^uPJ6F^c<Sc@k'G>VQ>[3>dCqaYdCPH_&Ncu7RAw/;eLZ>We?VG%k"
"1(VoRFH>8fA&Pe$G4ee$XC7PSOv:5gC,Pe$a[n1T(1CigN)72hKiH_&bwNiTL/[ihQD3/iMoH_&m<0JU-e;ciI>Pe$RUee$lWg+VZ.gcjKDPe$tpGcV19o@kY7c`kS+I_&u5)DWW=1Al"
"]R_]lU1I_&*Q`%X6mg:mQVPe$^wee$)m@]Xf<<;nS]Pe$a*fe$42x=Y;J`4oUcPe$2JXuYcK]ooha45p^II_&7f9VZl5:mpSoO+iHBfe$<+q7[qJhiq[uPe$lKfe$AFQo[$5EgrVr4fh"
"#_2P]nY2Gsso`csfbI_&J$j1^qu.Dt&Y=atYuoIh-?Ji^vF=Aud7Qe$wmfe$TZ+J_8t?(#:i###2Osp%,P:v#91Is$_W31#,(_#$^C=,M$f(T.-S(Z#1+)t-_@4,M-bLDNA02iLHCMX-"
"3Dm92SlqV$Z4ofLMb2Z#g)*C&QfCv#WTD#$5b?$$2rq;$817W$EriqLtwVv#vtOn*=J$1G/QPF%U)4kOW7Is$[36X1To_;$7snNORMlY#8%i;$X)0(/2`UV$wgDe-3>Wt(pu$O=uf&Z$"
"^`/RaA8Et_(YtGM33#O-2+)t-e_FgL@=5,Mf:45&Br'V-2VsbMWN<+MM2Js$whGv$QQBwgx(]fL3)/W$6j;t_)cKDNvWY,MNtM;$9=nS%-AsbM/>Ss$_<.kt[+r;$;@n8%(Jp;-:xt_."
"3iLv#%VY8.5=*T%N;Qh,N0Lmt#RnktnV0H4W?oS%gF+gL/rU5/=UI<$X4ofLi@]s$6rf(NTq`;$'N)E-?C_%/1chV$U=D^6(]c8.;4Is$H$)C&feC`#9Ce8%97[8%5rUv#2fL;$2f_;$"
"K%+n-vHHh,Vxh;$#I-L,8sa?$5.@W$<C[s$:Yob-Swqjt]7%<$^R0)NCr:HMZK+9%^9.<%<17W$#u,Z$de8v.2cU;$`qS*@Z.r;$f[bGMcjrr$sixV%2C(O=8fo6*OSlY#GZde$vBn0#"
"XLN5&V>fq2,i'HM4+s;$/w)I-7g+RE^-,n&@e'OF*+2W%S'4,%)VbGM$?]s$%1QZ$:7Rs$:4#HMt;^;-d4;a/?Fes$9..<$Xfo>$^Ohp$v3.kt$fQn*_#&$$3o_;$Y6.kt^I[s$]*rjt"
"_RN5&5]:v#,bep&@[ET%xn#Z$ENWs%dCxfLQsAr-;&xNORu6s$.#?X$8b?v$un5?$>Cn8%1=L#$SV_@-8O`X-X?Rkt+S4gLRkUH-<+gGMPfC)N`TX5&OAi^o45]&#iE.ktqf'L5]X<T%"
"mlbW%;x_;$cL4gLcDY4/:@Rs$[3.kt+S4gL*LYGMHG/W$1`:v#@Fes$Xtqjt.(-&OYaHT-I0RE.;7[8%p]A['rwqjt]L3T%jbOgLm:jv#91.<$`*rjt(J4gL1RV=-E/%M.AFIW$V*Rs%"
"3eX$K+S4gLdbnI-QIbn-8&L[0+_r<%8@es$@Uws$_=+gL%N>gL0JccMwauGMJL<+Mp<8W$BXw8%TfH=.F'X9%6+)X%IZCk'2o-W$,fmHH(e31#atsp%)@dZ$@hjp%kbFgLx5v%.geFgL"
"w?,gLfjt5&(fTp7HnB#$.AHO+ZF[W$vuAV-l#nT-*Y5<-=Ek7/<=nS%fXX,M,(W;$8xh;$fF+gLW$C6&]i@_/ft8m&:fCv#A=1D.L60U%I[Zs%lR+gL%rbT%jU=gLWk`qL^>/W$9u_;$"
"lb=gL)UFT%W*Is%77h[/Gt/6&@(Vv#1t%t%DbWp%ch0HMTFP%M'_FT%m$c,M31^gL5p(-MSkOT%NTg6&9p>pLYp,/()pAr-1.jEI)h31#)-g*%e3B6&F;`kt';ffLL.)X-8<?tLpTZa,"
"S['o-u'1O+c'06&#:;<%>LEp%;?040:uCv#74R8%sc=nE*QJW%7.[8%'[@9&F*B6&>X)qi^=R8%F-^2'r[p>$BFL`.PB9U%/(IM0Jts5&J00q%lbOgL/6T;-#$?D-ui&V-#d&V-*a<71"
">uu##?Ra5&KB#n&AP;qL;wtp%;rCv#5&,T&:o8,MrGwAOUjXp%GU*9%tBGP4WN^Q&H$BQ&H0GJ(@lqr$Fwjp%s3UdM&e(HMTa+t$heb,MwI,W-_ZwktoAed+Heh).eebgL:I]W$VGU[-"
".c0wg5_Z;%'CVW%@XNT%QJhw-fLOGMWpF9%H'tp%GUdX0@$Tm&GnnW$ceB)NQ@rHM+:hQ&7x9wg$7DW%ontGMgju</F39q%n*:HMZ0#S.J*KQ&3Lq>$cTn0#6Rh>$F5P[M012X-dH@kt"
"GcuP'%de'&jvqK(-MCh5`12$#P1d##ZB*9&OEpm&67PF%YL3T%#R]5/?(`;$kn'-Mcg'6&vWq'&u/mh#W..<$Gq^-6c*Km&Y5=w$?InS%?RET%]=%'MMB8<$kXF,M>O&<$=F[s$DkET%"
"Talj'cfDb.mNY/(?xh;$A(5G-9fYs-re=gL,K_6&L-B6&otbgL_aos$Bkjp%FKlj'.xm6Na()$#DnJm&pwbgLc<xS%2g]8&<O1RaA8Et_3=hHM</nE0MkNT%G_ws$>9*I-fo^p&Y`se)"
"*q36'QKpQ&),TV-vVGF%h-X9%Utnf$h6^Q&9:@<$Id/T&fW3L#/Tl'&AfTp7+eis%9.%W$g=n]->Ym92`qJm&qOs9)bh3t$>Ek7/FhsP&mhXgLYQJW$?Oes$G'kp%DE04(VdY3'FB>N'"
"O?b9%ebtGM-OQ3';fYs-th=gLE'In&O?gQ&OHpQ&E[ws$h_FgLL`;0(^AxjLs+@20:Le8%SN>3'./Y3Fs7jERX.i;$8+9.$I6.Z$1jPT%kpUK(/JB['tcWe)GQW8&?xk'#[Fm##Pgl3'"
"[&2k'/;pr-'OC-MX^FT%xB:-M7mvN'=LeW$o^n0#m?T6&YjPn&$H.K<l/c5&Kdu3'U?0U%P9pm&C[e<$p-.9&FI7W$D^JT&MB5n&v>332D=Is$CI[s$UZlj'`;`k'9.?[$N6t9%Vhes$"
"Ld(k'7v:d*man0#qgp6&l`(O(XdPN'Vguj'u$cgLlZLQ&FqJm&XHpm&WZG3'KFD$#kL4gLF?Jh(nLxfLf&Ek'NnwW$t6@w^OL7n']suN'X,@d)=o8gLifmN'Z,mn&&Ys9)$8gb*LgsS&"
"dAYn'cidr%FdCK(a5;O'@rf(N_gkp%kmmp-r5Ke$a$g2'u.i$'4#%@'2^l'&3%cgLG=hQ&lOxfLT3NO']Z^q%`cQX.Gn3X$?w37/JU@W$fOxfL/94Q'T^Y3'Pkws$GtWT%RWgQ&h`nH)"
"fS@L(R27-)^)qq%k-h)NS'xIMwRJL(_ArK(0UChLfG6n&]Yi^ofq&6&I[w8%F3c?Kf/pQ'EXEt$W#mN'?CMX-pw$[^1PKv$H5P[M3?Gk-vc#+%,[%T&4fG<-3lls-6N@iL.Uql1c]8>,"
"TF35&`Ji0(2t?eM-<%eM_s96&w[@m/R6Ot$OjCg(.GPS.Yv(k'VCCQ8XEZv$iF+gLg?]-)Eim92kaCK(n'cgLa8CU%?<Or.TNGj'I@Fk4+u*t$J0'q%Uj5n&n.tE*jfeh(UD[H)a5$r%"
"n6q)NU34JM7O5.)cV@h(h5)4'_pY3'_jP3'M$06&Lh<T%H6c?Kg85n'Hhj9%]8;k'@CMX-j:gE[&<V3X>9Qe$W,>C/<e$iL;f(p.fi@l'xlC_&11r@,Z'Lh5#ur$#oq2$#^PIL(mrn-)"
"#$4L#@[:hL2LPI)ZQ>3'fMr0(a;i0(G'k9%hDi0(&&%@'#Z71(nvG*R-nY3'P9g2'XVeL(g,H7&a,iK(N9kt$=E]5'0M:l/Uv_0(Ugp6&9Z1Q(L<>N'U&7H)guEI)q%JL(aTp2'i.9B+"
"R[*9%*_LhLn[4.)K43eH/DbI)^)p?0oPVO'e8Dk'&J#b[k6TQ&PtET%MNCwKmFQ*Rsb`$#[5ed)qX,(+VH5N'oaf<Chm-H)x;Me$DnLhLiwMk's.+hYQR=w^,jr0(<O[Q/&7L/)kJ`0("
"wRX&#:'&kt/s[h(vI9+*''4L#/-k-$@M'f)X2rK(iV7L([Z0:%WDe)*2Plo.bDrK(4(9U)8^:N0Fbw8%sr[L(0[_hL6*:6&WWlN'/Hg/)$+l3++6Kj(DJQt1s[3kt?OugLn)h'+D]tZ/"
"]iN**kcvR&0QgN(w@XI))ikM(Rb+N)qinH)t@=i(mceh(ilnh([ap6&W)Dk'_1g'++RU-M<ESh(u0_-Mmqk**dBb9%hCnA-11s..v^-.M>m:l-8kEt_(5bi(D3j#M%>EO'qlr0(i`@L("
"C,xiL1,/L(M?;'#%7E$#j:tI)U/Hd*A9rhL1TIeMsi-n&o.4.)oowH)YdUg(.$VhLlLxH)qF9F*Cpk2(+UL-MbJm/(%tH.Mf=YE*^&QR&XdGj'WpCk'QUw8%]ARh(^8dn&,e+1)RW(0("
"]J<E*qR^F*AErhLvmv/(ukcZ,YqNT%rXK+*U&$H*^ELwK&@$G*tXKF*%,]1(qf@L(p]7L(XQ>3'X<06&vxrk'9wLhLG#PI)LWgm&#MKF*6k)W%du?]-sAM3X7(6c*CK6I$-EvQWx,67&"
"S98ZMS:7M.$seh(73Jp&`p*I-AeLhLU<FM0jwJM'%%hF*4RM`+9U2D+Kd*JMu+wN'#cK+*xF0F*a)@H)PM;m0$Gt**$uGC+v.fL(AN9T.O6kp%8mOD5kcrK(ko&b*TZBU%iJ)S&L?BU%"
"l`w)*ag7_8rCJ1(W5`k'g+Oi()xKf);Cv_+kM[h(6wwA,S^(0(F^R.M.EE-*nUJF+/lp'+3LQG*)]T+*%lg+*wp&7'fo*.)n9I=-&%v_+?Laf1h5@D*kUTf)7_dG*(L_-MQ(C+*1x*a+"
"7,iD+Jf&gLF:C+**7L+*,?k-$@UnW_=rte)BO[Q/D,,b+.Vke)KE`'#:ea$#$:))+:nr@,8v:d*5<4L#-^Dk''-x0#7o5c*Vm5r%Me<30$c^b*04-c*d@H*RDqUhLxI&-)p0)d*/Mol'"
"&J^b*a2?V%#*Oh#*fao&QWpq%s1''+x[pF*p,$7&aA;O'tROI)@?X:.>'JA,q6iw,045m'ax/F*UJ%B,^)&iLqN5>-24Zc*B$s@,,(_+*+itI)k8vN'iDdR&A)4jL*OG@0lD[`*r'QG*"
"B.Xt(:RUhL[hdc*-]mL-X^S?M&lVI./bE6/FQ?I$C<Br.@0ihL/E'R/j<oY-,H0I$ak:.3V#7L(C0fx,JptY-=fa>-xh.T%NaF#-utl_+:_M`+#&ES&okuv,;ki%,/=m_+9b;`+BEw*N"
"&ufd)wdR&,7oO2(.lPC+hPvr%jM@H)l#U6&Pu;H*$iPc*'6nm1ha#n&fvGn&7R.x,YAOjL9/O8&'V+Q'6ZQn&%kn=-LW4#-Xm]x,*6(<-Bei[,HZf&,<_``+6eVD+#,Al'rX^F*&9g7/"
"6tw=-F(7+5viW]+#LD)+Ljx&,x37x,H6&a+np^Q&=UN3MHk/gL*&N`+<_v^]QR=w^Mtd(+@x(t-hhhkLZQQ(+QmI(#M9'%#46xA,Mv9;.W8Lv-]#JiLKcCv-+A9F*A*8A,:n@A,_D;S&"
":6o0#D=HG*B38a+3oB+*9PPS.]m#n&:<sf35rBj(vii0(x4B+*#X7x,^M3**c>0,.DwChLreCJ)h4kI)%=vG*BB/a+Tg.[B3AK+*U]Vt.bG[H)ZG=/MAoU(,E?cs-M-e,*TP)T/D-Ax,"
"?34Y-6CvC+oI^b*s=,_+FR;%,VdIiLQL,&#,Cw9.V;4jL#DOE*LWmv-0>so&<NYO-X#%i.Y>Uv-JHl0.SPBkL*cpW$SP.21KT7iL=;Mh1q6fY-XDY$0q8^`5`PNI)U2qV.ZcZs.C@5W."
"bYO/M,%,.)AHo],?n%],v75$,5P)C&Hw.],MjIiL4*wc*0:Z(+R#e>5a)H3'VgF^,?F?K)&)8L()V5c***=u-/:l3+5B/A,(+(/)F?f],lu/b*'IwT.G26W.Y;G^,<]ta*M].I2#'Z3'"
"J1`0GC]?W.oPZs.e%*t.LA-s.U?j)+Dk;D+D[)D+#/Xe)vP;k'M3[G*p=)RN8Apu,0?4B,ZS:_,8w-iLJRFjLnE6n&?#9;-NVjfLLILD.J8rH2Y3lh#_u3/2B0S],PY[e2h>Jb-8Z0I$"
"<lNW8i(gF*l@AQ0r$5n0%(#R0okfQ0dmN-*RGX/MSY@a+0avN'I2Z<.Ws4B,Qmt>-aDq;.=$8A,@wr%,wrIP']u=jLb^xi)NN0;.(]op&,`p^+/&*4'#4;w,BQBZ-MJ-W.(TV0(()A1("
"ZA)50x?uR0U$vQ'F3n0)XiA1(E)+jLFgwQ02n5?.wkS60lfv40qhst.`PQW.Y`Q<.>LhJ)79+#-EIpG3Xi%Q0fS=jLNEMS.?;-[-utsX.B?RiL#/wW.2j)O'8+tB-<U>[.q1Iw-@,TV-"
"[Qq6*[P$<.<Vn&,ki1Z-V#`1.7QXmLO&:v-aet20)a>I+2l*J2x$gq/8-712..KU/6thk1`*[(+d@aT/bYZS/9O3U.Cr)C&jimS/hqk/2cM1$-I6JgW'ei<-ICxU/pw3d*9Rv*437c6'"
"9CDw,:Psk'.ne9.O5dW.,&5[9K&Jh(3P4i(l:+j16H322eZin'T#K.*jF>i(P['02L5^V-?kc?KWg2I3rOSq/6hC02f.eW.fiUZ-B@hF*@ULj(jWlr/pLLkLRnN71u-:F*$(102^:G2("
"x@Wu.s7NT/$WGb%a.hJ2wLlQWf+39/%7AX1JIK$-(fns.kI&q/IALnLXcv8/uFF&#tUB#$(%$?$8oRfLP:$##q++,M$L@5/5FE5&P/p6*QHi$'%`'B#U1FcM']#<-?FKcMAt&.$&i]`*"
"UT`l8Zv[i9q%u+;dG=J:gop(<-[FV?Ak#&+7Jr%4;cR]4?%4>5C=ku5GUKV6((N]=(x2A=Q6do7^3:fq.)Z%bj&3`st.C;$.iqr$2+RS%6C35&:[jl&>tJM'B6,/(FNcf(JgCG)N)%)*"
"Cfw4A8QZlAqb.>>XfW]+gfOa3_-4&#c9F&#gEX&#kQk&#o^''#sj9'#wvK'#%-_'#)9q'#-E-(#1Q?(#PUG+#p[P+#2r)1&;rf(N8UC]Oi++PfS7Po[1,k4]I%1P]CJSrZ'=?fh+[;ci"
"W)2Vdrrm:d>^o@k5H4]k;aOxk?#1YlCA-Vmf2q1KO_`uG>M%DW2f4VZo5YoI^/LY>5Kk1TgPBf_Mojr6YoLiTPP<MBG^s7R_wXxX5;v4JkY]uPfTa+`98/87o4UoR(tNlS02;PJ$l1AF"
"SoIfL$Xc4fYk=ipx#;YYn6B`WrN#AXpbi.U%Q^(a/$3DEhhEcVbCIfU1V#/:P=h%Fox.GM3lj+M;X(AOTQ9]bKId._iuIoe7*h7es['Mg8VwLpkVRuY5ar.CDDSfCaIp+DJiOcD?YH`a"
".2WlAigWV$$;d'&3R=G2OT[i9jGv9)>^6MK`)Mg:%1PY#CiAE#/$]H#r(eK#,Cno#:,_O-<Bx=-Nsk>-er?@-7@KB-4+1Z-:u(s-'nIt->ZXu-[lHw-fV+'.p^$>s1JAxtRle+MO5$##"
"<Mo'.huclLYbj,#sK8n.iQD4#-=o^.dt(G#2nVE-Q*8'.G0N'M3+8=-BN4>-IsVE-m;WE-@/WE-:$WE-*)8'.G/`*MZM?##c,X$M-#5$MVI?uuI(>uuo`<ZMC6L*#+=/CM5[onn%A:F%"
")dGxkf>LmLW<dV@e$>xE/N$rPEQOCM4CvhJqG2xEkVpU5;X8egof6gUIwcA#vOX&#]wMe$Ckn-$YWo-$#mh.U1fs-$3Znr6e9%###SkA##.F7/n6#F#E_XOM9rA,M?.qV-GdMk+p7rS8"
"#Z53)Ul'P%Ymc)#<i=6#ag60#Nl?0#5rH0#N+2,#<n@-#A([0#<vO6#IHd;#MNm;#'5n0#+A*1#0G31#2YN1#7fa1#;rs1#V%^H8DIsAF_=R8#gIe8#kUw8#W,c6#Yb39#snE9#w$X9#"
"Q9J5#0Qo5#4^+6#]%.8#X?S5#'7t9#+C0:#WPC7#r1@8#=<Q;#4b^:#9np:#`E]5#m#-;#A0?;#JZ)<#Sg;<#YsM<#SC17#73A5#kG8@8p)sLD6wq+DrN#AX38[%X5Bj%FXhdxF_KG&v"
"Ru-DanoYj01O)##S][6#1jmx[cNPf?c3X(N=qME,;[u##gfFT1_d./1h/mjD$MglA*x0^#X7;X-O>d'&XWp?-BC3p.7lTA.G<tI-;=`KOheVJDHG+N$Vu8gLT6hKO'VRV[8<qlD%gk&>"
"8F4g7*Z`C&_=r`?G%kB-uH*nL'BL[-v8Y'8v-)(8CNjt(I@K+Mw56Z$lTSV[J?WC?S/YALt34g7RSHY-Z]MZ[=cQ][ekGY-(;`'/&dELYLtR5K4>D_]+Gu^]LvsjLEh:dM=[sC?5m%V["
"<QeOOwZna=q7[V[)PDl+%Lc%M;>Mt-+[enPU7-###YjV7@SF2_$TNjLnL.p.M1#/LpeWnL;5:Z-,.'=(X;_;.:rDi-jZ-_JtCW0;AglmL(`rY?_$Y6#_7?f_(J:;$Q5qB#8CP##'V,<-"
"R@EZ5*wK'#]_R%#1####l%E7#7#S-#_Ja)#G-W+Nfwd##PF.%#>f1$#6CDX-XUq<:aE)^#eZV#$AJn+@uo5>:^HXS%`6i;%?``*/pFlpDjOc9DHqpx4mGKxk#P#<-$t;Y0&w(,#A,78#"
"6oPlL*+p+Mi2cP&;RNP&Gh]6#m]Z6#dcd6#t5@Gr<at2(^Mvlf<-<X(3>NX(0m$@'2MSq),<,F%#w+F%/%L:#sNMn3%ej-$=5GB?b)+,2xXN#.E:woLD1v<-2:;X-fov<(c^95&TE3L#"
"''0j0AWQJ(]H7g)JH/i)13cP&hGJYEv;a`#KX>hg)v`2g&TL9MfOfYM/^^2`3[QZ$-Y:;$`coF-q/&F-tv5D-$36D-E?FV.DsF/(SrX?--*#O-#cg<M5aYgLkb*mfV43UDpH+IHS4KaW"
"hojqW$[K`WSOO/D/Q-lF*Rt(3RaCH-2n%VN6&g+M88GcM=PP,MPr+G->hv=0s).GrYc`B#Y3?b@P@]luZi:NV*>8'f.b).?)YXgLr8N$#oM.kbQr68%_#Av$jaIs%Ll`a-heT#Iw$g+M"
"K3#,M02#,Me9I#%22*=(G@JbIMUSbIJU+9.DA2T/:%1N(+3xb4g3=D<,MP^MQE+[g/61,`c*`p#xRB?<XfkZ$]Yv6#Y.xfL0$0j0;S+^#M0N&OW%5$M`Y[M.DNAX-Q]w/D$mcP&#h'lb"
"eOLcDtADL1_Ca6#icd6##6@Gr5.CK*(:^L8^HjqiXTN9iJ&###:DEl_,wq'&jEAN(073Q/m[IJ3)9cP&0oWTE=&fn##ESX#X;MjuBh-H`X#kwTaRaP&La=VH(b,68s'&9&F']V$g<)Z$"
"f3d>$q^sKY2MSq)M4uJaAq668f1?v$gi`40+3pL_/xQS%C_-lX'DFcMwp)M-xd'`0>LI8%d#3ADI)2MMWZ#eutg1ZusMQn;Za0^#&:ob/-Mc##<CXS%6Pb>$&7vV%P7gA#i6H_&ko_K_"
"Na(RW%3c'&(@e;-=3S>-sIHL-b8Hu7_G'/`G'D#$b32?$]O)##%jtP_v@e;%Oj</M$MbP&Q:gA#b[k*%VULZ$3)@S@Y(d;-?.PG-5A=?/ZCa6#<P5$MfMAGre6+gLMDLp$8.Lk+==Lk+"
"'-,F%&]U58X`9/`0K;qMQY:;$6bb0>R,###-:pK2Zn6g)`p;qMa&<qMgGe5DEoFeuMA'Sgm*Yp7g./9&,l[6#T97I-I_CH-kPWU-/)vT%[vfQjX>kKP,#<X(=5Q/vitr2M=OhP8:gTN("
"JfnU/=JDu7U2U^u71&t:j<wo#b;CpLiiv)Ms0D6&ckJM'`Z^6#X97I-ZK7I-Fx=G-rP&7.CV>$M(%w##*r+@5<V%RN4V]q)fZc6#&1NM-BF5-MF^*bN2#us%HURs-NJ].MeCYs63R5bI"
"S:NP&0:-/`<]F#$0i5@$_b`Y#G0xr$V<SC#i`Pves')W-Yh)R5S6)=f`_1GV$4B>5H%<xb:'`JfXn97DR?3L#QxdS%ODg9;'u7KN&@,gLO#@68w@vV%HI.<-jLT[%>@Lk+vJE-Z?vHW]"
"NIh29gDB99]hv##M[i;-v3-L-jS?.%fjNw9VMuu#75=1)6n@X-XiUP/(^FIDhuJ@tt?OpA#;.GVL2Gm8BPm;%F0Z*7>MYw9RN+n89H'/`d,v3FSO)##HA5K24>0N(WAu)4rEH5f:$Ie?"
"Rp[H#7<LdbVKbP&f('j:ped;-uC&g%Fn%684^Ds%,xt4%19Xm8c,[O(b]l>ujs>>5Ag1Zu%ZM4##tM'%BFm8&K/FjVZH:=%O(Z58J:-?$jKto%</Rk0[+4<%]x*F3g>f+4Rx^0`$TVXT"
"r)aJf,xQctc)mL9h&W8&:S$n8NRx>I*0Sv&/2`p8[Dti_8w@3kaKw870P0N(as4J*6_eg:Q6+LEkufP&;t,[`+u&]Xg6nr?K,H6/`2h'#iNOgLcDIEN]01A(L8CN9WNS=%/q>V//:$`4"
"g3=D<EC[B_UsTh#Tv;F#@grN`MhsZ`?4EtCuA#t-jNB=8)G;s%q#0<-B<%J&7mb;-?`uD%ipuERqS5n81o^>$*>B,Ml9xiLqAu`37rxP>4j$TEd3jqUbjbG#6h+Y#X/#[0&5YY#7Sc##"
"GJ63:lp;s%J>_/:bDCW-9L<?#Z_G)4FF3]-8?3l]g_KCs$>X7[^5]+iJNAR20m3e=<;c4Sk[ZYGY6x+2c0D,M@=Z6#tG4$MAaSGr^Mvlf1jSc$xcA*[5[e;-/N1h.:H/i)LC*j0FrFdg"
"$QE@t/(`[E'-w^#9D-Da(Z$s?^WQ&#xOE#.l:gl8InK#$Y`sS:IFdv$i4=1)Jw:=.)RFAu4Fw;D<Psr?%K_WM8D$##^2D>5LgI_8jt+'Q]C9-)EH<X&`qZ##'7lh2&n@X-Bix?2$*U:d"
"0N;7DCAaP&Q*@8#(EE(#uLE`WxH<8%LNAYGnrB-2BMOve1klgL23#,MDNM=-D]l)%.NPF%SC?thaK1O4R`u;-MlLa%-v#39gEZZ$d#60`CR[?T.Nc'&XXD>#JEXS%chgA#YW^20k-.+4"
"V4F`WQno6WkHPcVm>E195$7C:2i=W%ES`k#QAP##r5H>8G,?v$u+-<-N'4`9[s^>$G;l;-fGtJ-+SwJ(g9Dv$,)DO(P*X:.ck/GVhwxWg45X*RP)ggM^=*##WJ>%0vbiO#$Oc##1K3v%"
"6=<=--1^0%6Uxm/,=6g)616g)ir9S-nL>w.CwiI#]eCk=tlIfLA_F`W[)tQjZ%)Rj%i_&O/8Z6#^?qS-=AY)%95bo7rWFk2I@W;(QZrQNoNj;-^g9d%.%:hLfb*P([%Wj0wu9Bu&-EnO"
"Y:EdgLohW-F,-9gC3<N9qMF&#?SJ&#/X;s%i/*^#XJ]M_g]u'&a7V'SnNj;-Tteb%G2+8_vNmx%WbD>#[]>m8]mB^#*v&kLZ^67:3D'N(43FL#M2B+4@SMku$%*`u35aJfZUG19Lf7nL"
"9]$##`:a`#5Yu##s'A;$VK3L#b#a>$6;S&#oW[F%ZcCN9$>vV%`ji'JOh;ac?,0i)V#4jLTE4jLk1dI#.UjY#1V/p%1Q:l/p)1GVwE<8%ljaSJ-Hk;-sYq*)TXD>#t<*Q8x*p&$'Z,T%"
"S+Ne+O#Yd;tOb%Ts6+6/s).Gr#FgP8e)$Z$%A])3>TIg)$if1B$*U:dT5%XgR9dmLCQ5cgHc,t$wG2&46D<PA3.t*<#wbA#MZY)<*TG&#`+`W-0Q4L#/c5kO=G<BDtv>)/EFr2#S9w0#"
"*jB5/Rjw;%DxG$M*8jJ:K9$?$0Hl+MVD:p7n@39'4v`E-S6=g$ckY)4Jax9.@%>D3C[L.=k6x-#Zb5]OCJo+DNhVV$ESwS8.2QD-]R5U:U)FM_D1:Z$xTX<]48&F-h3n6%tx39#E7i;-"
"&a`&.jHbGMY-0j0na;hLfBsI3GlF(.bv.sLX67NuZAur?V[do7qv:T/wh#29@ZH+<M`6s.n8AZ5',0J3/juiTpkX2Dp16e@eb&oT<f0^uW<%iMw(LS-p:=R-'Alo$<Gpe=BbBh(7TNI3"
"G.<1DpjB5/eY,.6`uL?#$h1$#VUto%2735&i=,Z$U7`_$wwSfL/'Eb$kvPa<siEU0/mu,2xH+O=lI)<-$ND&..WND<+A^;.7fuo.Xn97DM_fj)tumi$3eEK<<`WV9hux'dO2Ca<rubA#"
"&Mja<&-LpTN:/GVjr0uLi@9WSF_F`W[(kK<Yjq=%Gx4^#LTq`$N^Pd;`QCKaMRAZ$1$T9.>.OF3DOEp.cA5GV3LKtL?VoxuwT/R.1Yu##2g:d;isxctMTim$>uh;-B*lW%3dic)*^d;%"
"?(.W-XaKtLhjTk#FNI9#&.$_##'>Y>kk3GVRm*J-TSSZ$jJkK3d5`]$x?&T.^Ca6#H>nV9Dnx>eJ)5%&AuF6C;_QM9n)N[$X$vM(JSi=.IwWUEq_6I$lOm1ZOnR<-Qg^g-]gwvnV=R40"
"kTSW-'?u#%E>^c$_J:;$%=SC#__j=.jQ/@#`4?PEP0pAD8YLJVng&<-;v4[$hHj;-J2]3%H6Y)<?#$Z$na/<-_-S+%i'jqKRrpH':2C<-PD=k%$)FwR>_QM9]^Ca4Z_G)44W5g)7hEr$"
"=heERbnX:dk1+9:MInwTWExl/koer6cWap77]X&#`=3hYYUSF,L9a/:XnrI3Hf*F3=5,.D$%3ADXA'Sg=?YdNTx4[$g4=Kj#e>W<'d,L:q3YC-wqJfLP[Huut.>>#bZM4#)KNjL^@6#>"
"Ooti_FbwZTc;mJ(%Weh2Mp^#$Rj5A#66Z#UN4[)HZ6]fC$C_fCL[DW#'q=-(V4x6#NP=4%UD>m8Ior8&OnbE=F,C#$f>JM_iPA$$/Nto%bV95&pA[*.>0;hLGk1p.$9.(s)fesoBO*ku"
"Swl1M`uN$%7l3GVu^S92C11f):<bqKL`T(OZZ<7NH*k#NtI_t:Qla3MS3$>>UANwBhkH`EsCX5:jg/+GYxt4%$2QW-_(?eObX*g;&#;I3_k/GV:P[eucI<BDx<ck<;_`2M@9AG;=]BXS"
"C-5X8b:*t&LGQ>>A6*D#2*/i))L'>.Cw`$q`t7spU<fw:T*Rh#iL#C#a;VY5:Cno%X_H$MW1:P%bw>e6k:%T.DTY6#dl<Z%:x^gL*A's$I#6X1T>uu#)n%v#[v@;$%-'u.,A;J3kDsI3"
"o(3`u?ZGXg]'AI##Uh4A$,Guu#oKB#hf($#/D&%8Y3Z;%/g5=-aTM*%9RL?%=_6m8`Zi^m0D#S.15>###?tP8dJP^$V:.<.LgfX-k9k=.^2wx42DZ:dXTB>5$rcBSn5J.#tlw_SxXH$M"
"6kL)Ntl0A=8<Z;%``Tp7,H'/`pKmFIrY@v>Z86Z$q?]-HK4Y^u3Pr6D-4ED#5nLqLg8-##C%PB#mf($#lsYU9PMjr9WHRe-obrsfh9Ej&:,#^?0>M,;q2j[$Z02N()w@+4TU=/E3@k3E"
"d/WQ.tJ*##M[2T&6L8RCb&hx=SQtM_2oUV$llhE)XJo>IN,u)<N#1^#s&Fr$1EBN(<IHg)UR5^u9GiT#0wk&M+D<>5l;_XJX[d##f9%W%8T)Z>bYDW%I<=8%,60<-7F5-M54Z6#QIKZ>"
"up9/`=f,eQ8ZNgLPGx+%[$`;%F1aB5$4B>5:Pr6Dtt(R:V_?>#pc+##e,cP&m+FS7f@iJ:qIF&#<PfA#6V9gHJ0dFu(:#gLM7ie$k9Z)4LIWf1XZCD305#XgFs:BDA2Lh,I,P:v8w^fL"
"@29wNq:r2'7-*dtPPQ#>&J<#/#dqI(e$xJNBhqp75x=4M'.gfLt/;hL-DWY5%uJ/D>ENfLc^T:d0#s1D%/P:v^&vx4g]*KN#([?0gQT7/[k.j0tGM#PkZ;Y$0:H)4k02N(N`i=.qrv_u"
"4#DT#03AI#/i##5o%O-Qr9w0#8x<X8&n[6%kGGq;6SiG;T8>2_%9Rw%&xbe)kL+F3E=JqL?@/GVdaV:dn_&K1KgBB#79h'#=(V$#kckKY?/]S:9=1p7khB#$-[`8&WIl:>UPh,FN81*<"
"aa;<%''d6#hov<(d#62'l+qP'.vGW-SgoVK]mdh24#4jLpE4jLEc0i)(0fX-1^.OE0MGXg$*U:diY3OE&&f$TtZ&<-F%jb(nOxnhY-b(&/]H<-Pe/V%9Uw9.^q;kF+L>0DLWOeu7WB7D"
"OHY)%SWL/DJ`E_AdahEu[9)n>JM,F#-E5,2$40p7=Mnm04@'>.Pg;hL:Mr=/fqteuHaLqLHS6##%;uu#ESOgL[Wj$#[LXS%c;AclSUQ##O^O4MORQ##5`5<-[dNS8ALDs%IWef&KQXb+"
"<b($#YC8#8h`(_?NOQ##BY-H=TR?##*[b6#[k@+%Q9X'8a<N^2%:H)4mv@+4616g))4hB#[SD^#j^@H#*'.qrHvAkLV,ku3g1m&V(IJYEb#0I$q3n0#M/P:vs@*DW=XcHZ+p2MK?u1_="
"8EO2(j.r<-0=DX-s.QjMN>:*<N=kM(p>,<-?QYO-5De*&9Ke>$02q;-uD(d%/Qc'&OG>>#HouP':T=q&KI@b28cGg)aK8w^[g`]-:#G:.$tn<DOxiI#)XXFDM>C,D+WURTPKmJa))%i$"
"/8pu,eka6#HtfN-'m_d%`F[?T:8fKY,<,F%:fSq)SlUV$9(Z8&:BoP'AR,F%4T,F%+9,F%6Z,F%(0,F%]0A`?=&=+NJ>b+NUFHofDP.,)9wfG*<W(H;.;i$[Rdb`<lJ9/`Tgl$.^5Z6#"
"qNTC-/5/F-co]S'9>[w'KO5R*7jPF%A&+H=Kt_H-:9X7/tujh2ZIiU832v&6[A@^$6vsI3^Z.m0=b:B#W<=7D>dAGM5/EXg,f>>5HEnw'-lq0#r,#v#=oi=cUYMA4M,@D*vhd=l%gHiL"
"MgcgL@fcgL4.i`j7CP###=Nx@&@,gLTLihLbFXPAIGvV%JSl;-0Y#<-P-cw$6gPF%&@w;-FL.U.NZc6#)Vq1M3a9cj@,mi'FDgq9gD[#%%OJp.)>05`Uik,42/G$MGZ?##^k.j0S^5V@"
"X5Z;%)MPs%M^1nW=V<X(=p]6EP@1ga*RGgL7E`hLTT*r7POid*i4=1)l5On81=^;.R$G[$I/NF3c*Ig)_lEB_=at0#.5Gi;@<SF#FbV:di<m6Desc310[r6D5JMfLY$@##&;uu#3MY##"
"1Yu##_f0;_'pZHd&LLb=:0uNFh<l?.(F5gL7.gfLbLFp@YbrS&Cd4m'6p7W?.Jfp&''d6#Ln+[$QG>>#DJ%_oX%Jn3thWs8`o%9&IC@b2lXR@#,LaV$mMO1);HC^#cTlm:j*[@krdp)U"
"gA7g:vL:mTCr>#U)0eB#U*Qr#0Tl##wWA+%_1`BSVU>L2`0HF#9?,5=Zie_-LKa>/AW4$6fb82AU;Z;%iO%0)h&$7#h11l%Y-*EcY5Z6#ooKK-Sr:*%-?,F%u5I0YZF0:^57)=-iixK)"
"Qv?S@,BQpgx-,GM(<*n8c65F%D5wS^1'2hL#xSfLQLs$#vLUL0:otM(mH7g)Y:pM`u>^;.&3lA#9:VHEg+8wUYcRjuI965fPse:fX]cI3K[&##Bl<j.>waT#MgxF-C=Tk$2TxQE-$F$M"
".4pfLDE0j04@'>.1sDdg=3s&M7sgW$d(xx4<b3W-*$D)ls#gg'1/r9.[+4<%QY*h1VBM.=^[Uo:m0a*>6og#OELL.=>1C(##&P:vsXVO##h1$#-l`Y#ql7S:R5sm$p<M2Bc]O@n:/G$M"
"2U(5'>Fho7WUV6NRb-<6DAx<V/`e<D?n%$UpJV3#$&>uuZ<no#JZu##ePSn$x9_Lj'F5gLaP>,2SoJL(ZE'P(`5,.D^Wn6Deipqu>s>1DM]:O3uKAF751dG7c0vE7_*2F7W@Y)4sw(*4"
"Ak#xA'4-_#^%<ADC3Txk'$FF7=e)JhmgTBoS^cu>oN)h)&3lA#HxLt.AdMY$UBAi^04n%=MjsS&MTu/14qHH3a6v+Dx#+rT@S7m-d[5kO17AJ1:IY##8)%w>f+CB#+t`H_uDcH5'<5,2"
"laIgL4_-lLXZlGM2bj=.A_CkXu/AI#$@'i4)@EjL2xfAEEt)_o-deA#C5B:9F^xG;Sl7p&4x(9&et@;$DW`c5bPic)LnP^$$+1f)=M8@B8,)-E_J+rACFng4]DnQaJ,Y:vXVcb#%DHP."
"JbD>#4?.^#k]g;-nj5`-(S/kX=o0N(7VNSI$Ro7nXg`'#WVQC#%Ul##S$Y6#7Nlt-f34,M^GSh(8+'u.wv=T.3e&-BKhC5/4*51Vlr?wLpn#1/N-G`WN5bw9LI$-b^nKmA;;bi_[37W%"
"Epaw9nv.J3%XjH3DA2T/xr$?f]d/I$D87,Vt/Nq3tfa'#@;b+ig,PP&,uw6#209<-Lu>Z@KSbA#(%0a<]E'/`?`+^#9pTs-p.958FAvV%+Cn;-at@T%IwM^26%eX-_HF:.m(OF302tpu"
"4N;H#'R^]4qY@pUP,Be6FWj@t-iwr?hug5'g@Qe$r%r3=%3=1)N?X[ZBKFJ#)H&##(J:;$w$YuY.ke_/jB4OME4=F3N/2gE(P98@Itl&#Lar+D+kIdF7-;hL^#:O3Pt.sToJEB#6cWY5"
"a[b2`<?SX-[@H>#%<wo#pqf(%Wrk+DweT#$3,DA7';8_'(QF0uG7lh20uR+%($R#vl4)O#ITlA8V(*`#aO)##vVTI*&em_>;bK'@>Gs'Muk,L/?&@S#lGW?Qd7V-M]wbhug#<k:#fb&#"
"X)GwLt_d##fa=[&E_k5rK2^w)v-JT.qE'>.OoM..unJqL7`QiTt94Z/Gp^oIG4AMK:tfG*U)$K:MriV9gSic)h8&.M(dEkuRGuwL2JTQE)m-mLAmlgL;/.QQ,@=F3Y_+t?\?<;d#@=EjL"
"3=-##TEpV%7&w6#v?@g:/t9B#Fw@;$L+v%&K:c>$kas;-Q]FZ-5#=kOf2=1)HK8$MLYDdggoVYG]')f#pL@W8R[Z>#(#Al#B(6i(R-/Bd`K]S%3mT<VP2[V?CCAwLUu6A-WS:X1tXik#"
"FBP##:Oc7_Kbh[IOb/r%*Y81+#/*+&056Q8#+qppdmdh20m3jL=8xiL`K&s$vM3GVS&uIuvgkI#c5pi#o-g$0$&>uufm.l#R-%I-w5$R<i$UB[cIO5Av9*Y/fe)')Ms9D<4acs.8%1N("
"`_/,2:nX:d4WN^DTe;>G$El+V)1h'#9KL`WYumi'wJOoRX4[5/Zk.j0g0xfLaPEj$Zdk;f'@,gLI^]g:cc7p&i[Ip.hnd._t0kdto#>-;.<Z;%i=)<-:Kq6:w#(^#SRr;-k=(p$-(jJ:"
"<0s20BsMF3N1Br3>JSFXqYrH#'.>+60=P@14B%9#&2G>#19X]#0Nc##1'L0cMm>6/vsqFrat[fLffYV-?Qi]$O7/rm@.dG#Gv<D5#lhl/%,>>#/i'f#*ida$MSUV$x6wWA$^Gp%=nE:."
"iUd*.js%.#;Rl&#'I+GVUjn;%WK1u],WG,22%###6MSF-x@+;&25<X(pOQ$B$-<gLuZX:.W*-XVSt__#MaaU3c2Puu7H17#2W>;BfJV>?gV`p$HXj%=`?9/(*0kT`NxqKGxuNWS`)H/("
"s&aC#[%gb4@#G:.TF3,E>r*8AL%`'?+%L`$<uh;-rr83%JMB.=Z(O%.eM1+;O_bA#HqvPT+[6GDm%PKE&6,,2S(^<.PlB1V*XXLD;*'q9^BJ8%C^?D*fv#7#R81@->f.n&RUh,b.klgL"
"G9e68nUgJ)Y5_p.23pL_m>v6:T]LI;:3?v$P]b;%rQ)/`n/C<JFGpc$Mn`H_bEO[7'@,gLQA1e;J<kM(Soc581G>H3<6fX-qc9+cbPA+4x_;vWv[0B#q#MsB*C6C#_5]w:i>a+=YsOf3"
"v=eWfTTK1v#GGb#m(V$#2/'edR%RS%3*]W/*L>gLIF[aN:v1-Mg8E$#/>05`F'M#$6+oi$x:6<-@HW#&[G:<-qWaR%WRG)4u'd>5q2CVE(CGiTM9cV$oboT3@veI#@FaV$f4n0#M)###"
"%I$,DlhoBAHRRc;n;`*<*H42_xf#X$Pw%e_(J:;$.95W-Cjb>o*@,gL4lNF.R@Y)40r]e$@kSk3AN3I3pv_?f03K;-wX15/&)>>#]ROgLsS?##5f1$#uxIf$35^l8+?nLE$cXv%]Kto%"
"Hgqd;9K?v$*+OsQ;3uo7'w^>$vj)Z$&7vV%(xqNXb50i)XJl-$RNF:.(8k6Dr;l8&adA>#g5g1TMK8>GOUS;7OE#Z-2IT$Rd3C0%=vsI3x#G5&^=q&MAxwx4$K1GV,o(9#$,Guu$5G>#"
"%[l##K*nV:M142_j'Dq'E#)(Z:e%Y-A(oX8dpE]F3R-90^Gv6#]6>W%P;M30Aa+/(clMmf`-$i3&FQ=&kAFVT%U4G/1,%,VKXAwLZk`6Vmtmx6MWmD5>x-i6T(ofLNKmu#,wjf%=nr:Q"
"I.`l-LuD:gNOQ##WH+=-6l+G-s&b1=lK;s%=jK/)n`Tp7ex4kkMdXb+09)R8qfB#$jl#UM[:*9.'[b6#`HJs-b$ffL'9bmf<J7F<l1(<-akY)4rm.i)(P[^TB0&$U/s^Nu&Jn_:XY7F#"
"in*VQgQlo.,Q3%;Oi-naJ(H9i^xmS%f'SP&a(3MKvL6.22#TA=uQF&#E:3g)1`HW-8;HNsWw2$#ZWU9M_.bbNeJie&2D^E[OlCs-%(rf:>pL)-jvnDEFCkM_*Juu#u_2j(54rP'36iA#"
"SIe8.6n@X-/M%9.2JP>ujp(N0Qm43=Z%F%.*SwTE49c`OJKx;-E4K,0t_rk#?4i$#+A?a$N77j90YbA#B%^2rhGv6#xn.F/`k.j00*Z68aQ^o2@,U8%r8Ow9%ZE-Z`4OF3*o6E5,e6g)"
"R[nQ/o(QjuVp%$UunQNUoWUOE,3XDDH('_S^YCs-Z,BkLkh&%#vZIG)sGif(2[FT.ZCa6#/4)=-Pvs'%E([Bn>_q58n83X_,/Hs-xG4$MuFAGr6Xn;-NZ`M%:f8E<bi9/`CT=0lW6O0l"
"m9W2(shrM2(^/F*$Je;%e;:R/uw(a42)NF34'jc:fb7>#>mp0#Ih.##@kmCN-c5ju:iUnL;Q6F#*ou8.t@P8#(7$C#$2G>#8OaP&Z/#;HNtn<-hNan%,>mJ)nwHNB5U99T9kL)NkB,gL"
"HKaN9=*4m'w+Qs-B=D$Mrvv##>r+@5;&'<%8.P&>X0xJNL7Me$`+TAXvP=wU_^V^TBuU3`?;#Abiw&f3O(4I$]wL3`67YY#2Z4f_X<orH-l68%=cG$MOOQ##>'f;-G6u8&sr39#S(Jn$"
"$l.j05+,##K8$9/vRb'4FcffLwdl6DX8PmsPVh+t&sQS@;q*BG=wfi'50>A7&@,gL:3Iq7;vTN_5xUV$&R)##q40AFO'Lpp%1q=)Dp5<-(f0[%%3c'&Xl:;$v20AF#)2I3i>sI3Xt@X-"
"2/NF3ZQo`m6'lADcuQ_uAZ6D#H[;[:0^ZJrfh88@[AI59-;>,MrF_H%)u$KWmGB#GUVDs%vl7J&A#c;-dn2a%rv[O(_/Qs.MqN1D0G4JEk;LqL8hn/4(GuY#jf($#5f1$#?R:4`6%VV$"
"onNdt%.,GM/_YgLVo3j.LTY6#?>8F-foX,'fT)_ZN5+0&3#gb4j@@p.,utM(&ej-$T1*s$N?2Nu8-&2D$hV`E4LdIEPCN8%Q*@8##r^^#$*5>>Vp`Qs[Rjl&i%2:B`nm##,[b6#NY'W%"
"W*Is%2&*q->k?La-LYGM#6pfL7RGgLD5g(%Wqj=.o#G:.2?\?B_xcmk<%I`cu%m<f3Kp$##%/P:vn8F`j6%rr$WUHP/e'8W-DLW/s0v(-2bnRfLHV)K()2n6#9b*307RA8%Twl)4.6,+%"
"_v;4sU>gM#/Q*rL?%%N#LxWUEMpUTE]`/+%J;G##O4Z)%kkJM'Kv$)*0,%7#=AP##/7WM-O.cp7_*?v$Q__;%Bm0j(AvK/)4',<-x[&0%-?,F%JiJQ_33DhLR/T49?Obm'''d6#c-of$"
")HiNX;230*Vnef$.7Ke?J>YY#6uDW-QYV[]2NtR%t:`K_h6Q#$o$Kk$)SO<.q@0(4ZJ)B#[8`,24uMA+@'m6DnpdCu8EJ2D%[APU74#D+'IF1Dv;wo#alV:d%5YY#Y_,AON]=dbx)-M;"
"s5[;%gZ`,M8J.X$^d>RCI,-gf:1]e#UVZZ3jPsH?P2G>#m>Dk#3g1$#q2Qd(X']V$eLP,MV6'C-V%uZ-'OSwo3>8F-4(sY$[.OF3,aV,2;kW<DO+dnD_&):4_paF4.)o&#lQf.UcWx`4"
".;7q.57>##T7Q23*tH]OD3i.O'V*r$<ROj0L7>O3[g#O#k)9f3<8i?n0X1)NP5Z6#4-iA4%7lh2uqY)49M;=460`A,_p'-#Rle+M,'#I@nH=2_/WRw%T`;v>-g'^#Fg0<-Smhx$'-,F%"
"SaVG#>w(hL<]BBFfKPR(Z#F+.iTtGMs4pfL#F;=-5#6P&`#G:.NnX%$.g&D#i7fsT03$t4)($$UBSwWgMmwx49k[Y/';cY#suG3#E9f;-;vs?'/.DmA%eB#$gM5W-&M>PjQs=W1fopl&"
"+f68%:DEl_lr1(&Z9=8%=c6j9NXFkMqGv6#t@'[%)hL&#B5c;-^F-`%TXD6jNfF$gjrZxe6OF%$m@wS/M4+`#5MOFDSl30D$4B>5_E+HGhQ*gLT@u&B&8YuuIIk3.J+(9N>B2tMfmdM9"
"SCo='SIVE%2Ow,X=XHM9nq^>$3'/t%gx52'(PUV$^X;m'^&>j`?bg,&0'-M:(;FQ'd#60`5pCl-^Au'&+SgpTY5Z6#ikB&8,bRU/mH7g)JCmG*8+U/)-tB^#8QvNk+#3AD:j]F#*]L5&"
"UhHPAVOee-4k.Rj;N4X:kjf;-R'NY$Pvs9'5ecgLfFE$#-ht6#,Sl##h]?J8'E;s%5>H0FXbTMB)KQ?$[v@;$i6xr$QW<s%o@m;-.M#<-h&Dx$qrQpg6)$p%RwGs?1]F&#ln.<-X&F^%"
"3^c'&E@04N.R2P%$csH?(92nW]ruu#R*%1M0A_;.kelo7/bgZHsWRF#Vl8DGI)'3)+.BJLNOlILHJc;-&52U%PEsVobZ&%#(iTP&JO.<-S(xQ-Nkq).s#:hL8E%IMR`VV?DarS&U`+Z$"
"O@G#$%@e&O#G_6,U]YY#GJ4o$R<==-cJe#%0H,F%nEN^248tM(]H7g)ZXG)4of0i)a/G:.bUwflnET:d19(4r/xCi%V_*oLqqJfLS[lS.3(iZ#'bXR-4/Qx%f5mi']Yc295b6dbRSuS("
"WEPq.AtC$#24f#.#u9](w*'u.NqsO(,i5g)Z9rI3sVA+4fe$-D/ZURM3J<>5F5>O3CWZI%'6Q^TM']pKR-=4#A@%%#=dY?_#^_3_c&k-$jM&gLsB*7%:B$O_A$.Z$U*@q$BqDe-w:`K_"
"`Cf+MCQrhLIG0nfgp-F%7^,F%0H,F%$[JjMmP`t%`$fj(''d6#AQsb$H>uu#QBo;-Q](*%j=WEn`H$)*KDbB%8K^s-A,?IE.d5g)tkK4.'.;p7U=UB#H:2M;iL8o[94[W-91kZptk1f3"
"-Z>hgB$s1D%(IM0%)>>#NtZg#kk'hL[CY`86F;s%T'O<-U(HB<d:O2(Qx#T&F)1j(bUj)<BC6XhAlH<-JArP-=_Y1%`$PC-jYm/(7CP##)[b6#dW%-M-x(hL1@rHM`To]GxS(*48%1N("
"6oxfL[NF5&$4)VQM0.60XvI+$&lo*%pn<:E0MGXgjaq,Dc9A.#%,GuuddiO#&tC$#l=F['T735&gxhDEF(8o:gGv6#DKM2%o&<p@YF;s%:Vvs-pmMhLj7*H*+XpU/2SKfE_=Cf-dT[<m"
"Wo@>5MB<O3a:r<D%5YY#Al4B#wc#2Tjs<&>U1N)<N'4m'W._8&ZU>X?DT9/`?F+O4/Su^]8?g;-*lls-(kc29%2OM_mur=%dGgI*fv6Def&I)491@=AilPCs:V&MB$o+MBc+Ajs?NOFD"
"_9kHQJ]TPT)AK&#>^nDWs&=F326RAOAfEXGv2?D<OigPT582.QQxi&-]+kuL]id##Vp<6`=J3dXX5Z6#M<i*'QT439VN0j(3h*<--Y5<-'%_X)x.`K_3fuu#7;2/(__)q7Q*t)YaOcOO"
",Shi>G-jhY,5OB#1@aP&HxFP85Pe]G+t8<-6cDE-K7i*%]nIj9x>+j+:u@r%>G;<J=_QM9x6o?nRcXo$l7Q29?jK/)AM?p.6n@X-'3KNMh*mI#$xeH#+@j^16:(4r+A%=D`0]e#[OMNM"
"SR6##b.N`#HMFgLkc&%#n6mi'?nx'-*RGgLY1/<?4^9/`e7s9)$Z;j0BTY6#&Xa+`'G:;$DcPBARO?##([b6#27wP8Y:d;%>w9nAuh7p&P+/oUqIs[>'(0EY2tHg)VDl-$f.r*4$GkI3"
"KsjI3+JZe#vDEwLNY#w3m))lLsY-##&;uu#:f($#4ZQ;<up6LE)F5gLeXB8%4>#29-$oP'@)Ls-'H4$MgH5gLWhE?%T`O,MuX[*N=D:t%faf68$T0j(8./<-u)HD-t+KV-1lls-rUG29"
"HqC3t6Q#T%0%rP'ub.T.9,B+4Hmp8%DctM(W8`<gh)<AD$V+f#X9.c4a+NV60o/GV-H&##%,Y:v^7W`#5Yu##OaR9_o>_3__xnI,gNdNB(hB#$I-D_&'7=hPSZ.jOe6b7)#o2U;Ncqr$"
"q)Ts-^LOgL]5Z6#^_2&&.iq8.u?.lL*vM8.Oiwx4$3p&V*#ROEdn*PJ`F4JEhGJYEZ?+9.mOa)#10$^,$(aC,CMLZ-2>RR&,JP>uDpQ@8lKgY#9<6C##C:7#$&###mx6GV7FNP&oJ(uK"
"_wGJCE+sR8W%XdtTIw7,4IW/4HK2M%,I)W%hs>?%Co0N(H>mA#uCi3Eao/GVlxBpUV^A=DRY]'#$)>>#-`:Z#ar`mJ=/$Z$-vMF&2;9Z$/xc6Ej/M*Mq-'Z-xh5g)-q>V/,u.s$W:W^T"
"s?H@tHGO8%TCxvUMgsZ`%q5pLnARr#cG,7Aar9^#77<.+f0>s/D11JuMw`b3S8,@0I*6Pfp8po%g0C9r`gMj(]?=8%s%>W%WIQlLW%N8.+EsI3,DeC#;8ZtBG>*Vg5D9qu/XChO=v#FI"
"xa/I$bN7kO1FoEIO7H9in*k2D-vRlfc/4,2hXT`j81?lf(8>>#+T,<-Rmcs-hKX,M09]0#;UM=-Mol8IC6FM_KC1Z$NON>.LW95&U5(9.tWa+`(vE#$f6m>$Po&k$jKj;-++:%%(0,F%"
"DV5ljY9C(4N)-<.u^J8%Q@sAD,6m6D4[X:dBg:BDsFX&#a68g4D86`)u:m8./>05`KMw0GX']V$S:K&#x_K#5i>sI3lffwYi(mN#MSnSu;s;>G8$###hC)e.:0tT#a&a..3-u]:HpV78"
"D0)d*iQ4dD;drS&xss;-xL#<-dS&3%3Q,F%OIR/)Gv=R*-@dQs8UJ_6+L>gLi`Em$[Eb/:ua0^#E;Wm$O6pUBSN--&kuED*A1<g)=Bf>-D'A>-LmA(%8a,F%AUrP'4H0j(%J%X-Kw6w/"
"+#b.hB.t6DML07D2FqB#CPIc4AD:1VW.J4Cj=hB#tIE`W?9(,)d[jp9O`Kh&Ro1HD-7.K<K:-##TkI+%i^J<-]g#r?ROb2_Bc_K_Jx8Ps6A%E30Ir8.;EsI3Sg]G3BQ3D#+Vitib'vT@"
"J^rtiY=9<?7qa1Dhm.RMH1$##fiV/1oE$(#0`($#d$Y6#%36Q:vld6#q).Gr8CP##@NLK()2n6#4=ip.xx_Z-,M9V0QOH>#$=gM#j=pZ$[n1H#%xn6DV2&-Rnv*a*0s>=--)jE-8S]F-"
"/)jE-?9^g1Yc`B#*f`V$Td3c4>fW7M2dlS.qD7H#Q%/'.4thqLAkn;#G?b]#aTA(%`v1T%PI>L2tQC,)k*+]#$.Qru[Sx_Ov*GM#'O2W#S[R[u]bY1P:OR2(x[k&#qQfP&jh=Q/Ke[%#"
"t2h'#@2<)#Pc/*#iUG+#1[%-#k-*A`r2tr$q#=;$BSsx4d:N;7)sK>?(&hY?w)sc<*8H;@48=2_l@qO9B_'3_6?bK_1rqr$v?.6/a`;mfp(V3;<gHL,dFVV$3gsc<Jf`D+>uH;@@`w],"
"DxE^,euIV?#w:v-Q9m'&Rlv'&=Vg--i,f--k8x--/a_c2Wm&g2;LtiCXvA,3;qZw'6r?_/(@YC7`Hs.N#8wlLjxgK-o4m<-dM#<-%eF?-%f`=-lY#<-Ba`M1QPs6#$=M,#Lr+@5VA>qV"
"2gn3+OVhV@?-ew'0Wf']Pww?0WHX@0L'>2CWpmcE2fEa<j8Q+#CMi-2_AMJ(N,G@&Gr*=(NFk=(Q:+=(Xek=(ZU+=(mFE_Z<h=)#fOj)#dcv6#t),##+`5<-r@;=-g.MT.s;G##k`5<-"
"n@;=-_lls-cX-XHQ/=2_WcA*[(nj-$Dp6'7KdF)</ZrS&9vcG*JY)d*YO=#-:))d*OItY-D.9v-[<M50D.9v-YN.m0N3I21gJ#d3N3I21e]YD4YAu`4ndVG<*xFQ9(k`H_TjUq)uQ>X("
"xZ>X(%kPX(h*>X('k>X(_(.F%mBh;S$;`1N/Gr1N-/moLcH<mL@A2pLfZWmL,`%QM?6Z6#:#T,Mu-UvfnbqpL4LHR()2n6#GMGdMGMO3NRN?wfbJZ5/@.OF3Ze-lLDw(x5ofGb%SDl-$"
"XMpcNM%-dNZGb,N?IccM1EA+4kIV/)T1>)Nr=Y8Kl3G)4Y6;iL7_p=%F/uD5fseX34W7L(oH=l()OE/4k/uA#Pl8L(UJ1I$PI':)A0me<%axDFB=5W._Ee/Me*I>#:2Zl9v*85FheMa4"
"-tEr7SLTe2>YjfLJipm(3ZZp.#ZIh(HG29F-@o]usPps]==ro.#<2M:liDW.pS4j4rhw,8<4n0#vWs-$UW7d#:l:$#[1]V$N`e&=k+1'#I<=8%lR:b;+E;s%U8UT.CTY6#?wCi%H<c?G"
"*'1B#*P:;$-VP6A^&KK2BctM(+bd;@Lb)P(s=]-PEe[e#$K]X#fQHqU1SYY#r.TV-_<f'&__/2'g_Zt*G++B=)XOk2[$?/C6&$Z$vW-^#+TxS&SiM&F$skL:-q7`?Mg=d;SD0/`oRCs*"
"UO*U.Lax9.$a%b/Pg?$OT<G;$r8FT&VN>oR,q]5/tU`O#vi;TD=0NW@>bK'@7G8_MvUQ:vF82Ycm-WS%N[PGG*E,,2nB->%Y67a$*L^wA5gC5/?:H1DVrJqL'H-##L9[S#@qQX.b]Z6#"
"Y:/70af0i)$$F:.UG2:28G)1D^L<O3'kT/1K,6PJAEOVHjAQ]4h4XJ-VBg'-[5Z6#uhO$%w(49#K5S>-bO15%/%1hL0-hs$S3N^2l:B%82NlC3[`0+4'<Ph#n)7F#X.vs-`RKfLeP?>#"
"qQXe#[/xfLF5Hi;S:IwB:,F[>lcj)>=%>G-CH.>)r@E>f^XAm/&,>>#44+e#S6jE-0EuK.Wk.j0WuC<-?);P-gWW7%%',F%Dhjp.xeB_4D'4L#_Pld3<0[H3;$[uYl%w5/'8P>#-Qh9N"
"p4Z6#oP'HMU8QwL.6bf-2v3kO5AMiTS)8kO,u%<-ceH)%=<sE@RR%]C5wK#v%5G>#rrEH;L(1/V?-9T.%`@H#:nF58l#CB#>=QVQlY.C[=BSX-]IdY##$CJ#Zi?0lJ####2eiO#u8G?-"
"X5_W.$Y7H#;_gC-S'-l.mu)D#uoBo-6M2*IH,qx=tL7C#:6v1;2[DSIZIF1Dx@$REuue+M;70l#XYu##etfl:,?>^ZdSv6#);G##)TM&.M9PNB(w2@$H3xr$)n`H_M(D0_e;bBIYGm;%"
"]Xj=.k=AC#/:$`4t@)?#Rl2DWLR;@=Yu3`-(A%=D7(Qh#rO%3WWbZY##),##<[aP&>>H+<dJjD@#;vZG[p+RE/,N9)WOtlAko7p&L&(9(kmx<-X''V%d]_KlxJZIOGHN39o-=2_3g?-F"
"[gdh2<WIh%dH7g)ZxD]-,0fX-KFS:d(IJYEB;r<D$4B>5uWeT#W<0OE$,>>#ddEoRIb%%/'T#M?XtFY8CcD.5>'Gm/&)>>#YD;O#tO.Q-)8N#(>%ASq*7GcMJ;&n$N5P3)JngC'$FZ)4"
"Lt.i);5vjuIY?)E%uTB#seaO3f2W]DPEn34m@0B#1wYlL['3$#>(U/@v3Z;%#W1T.aCa6#/fG<-2#m,%_35R3Uc:;$WIQlLOEKO0+6@Gr515##l36*Ng5Z6#3S2u$.B,F%S6bA@3u*qI"
"=jDQh&VRpIs*vbu,b?a$B-9<-A:_@/w#%Gr65Ta<'-FM_(3w^#%=SC#cGgI*'Vm;-IFOW50nNXAq:Po@$*U:dX52@f.[n-B_h$HtDb)xpHkPwpi*qwpwf]E[hlD(=^-42_lG3U-f^p[N"
"^^XCM>2N$#qI)W-KU3mDEj,gK^vAa>wSEm.>$s8.m;a2/[OO2<V.&(o7;_rAAX-T-mu9H1wk.l#eSl##GF.%#%Jfq$:9_3_WTgZ$bgpl&GQN9iB.3g)uHwP''bwP'BBW8&.h7p&6Yds-"
"V2RhCecD^QF[8.B=/oP'7o)<-/dYsH`pI3kqnq/#H;&Grnm'hL,Mj$#WN<$M.4&GrD%np7]UASo*Vi;-_/NM/,1K60_1v)8#aF&#D#Q#6`%B*[XFt@X<Tk;-NM.Q-R5`P-OfRQ-3fG<-"
"3M#<-ZqkoMR)2hLH?VhL9klgLD^IIM>tFX?S_d.mi.pPsDc'I:J:4m'tv=K)d#60`J4P#$l%&^$h%kA#bmD2_0SQnV'@,gL0wCHM8/gfL586>>CR(*4)w@+4gqdLM$br8.*q;GDfS(U^"
"_FC:rK<Qgjl9kXcf@/nrn####&%720:RMO#KCP##;+f$'Mf&D7bGZ6#k<e._Df?R97eB#$;v4K24uv9.1JbB#HbV:dBk6xt)+,D%T2Hp.sS;1`NAKt:B%OmLNLH##ECju$H`Z&MrXlGM"
">EZY>#Lb2_'qM^2q$;k`;1O?UMFQI#[)>4UMD@tU^$Z'#&[c4f-Nxu#6Ps1Be(49f]ap6D%=FdgKc8b@*U_$BGd#2T=wfi'(prQ_$4pfLCYm6#3;G##5r+@5g?Uv>'(+Q`L,qx=D*L#$"
"(R_p$baZ`*uKpT%dH7g)J=Hg)X02N(sEHH3$9.(s+fhP&UjNXAMS@=DhGJYE`wq:S.->>#^=@)X,%Q-QBk0rgnZf()@L;[5lg<H**$4Q/%a5J*:vA>,]c64Or2lX:AQMh*;1R<-h>&n."
"xk.l#0n]N-&7uwRq;)5'80_Kc8t[e*Paja*fR5NK([F&#,tJW-Jpx>e_5`@.B3I_+(1F%$PSMkuhfVGRqkCj#&g=u#5p[H#Pmg%M%U)v>HuK#$T)b+.kFl+Mf]c,25nMFPOT.x%9C8<-"
"Q>')O+AeDc5?KF%H[pL::vf]$x&lA#(pL#$b]l>u%c(Zu**PY#SZ+Y#LXVbRN2>>#0=aP&?Dupp:2ZP&,t`^m7dx$&rr_K_-Suu#682/($vgq&V<SC#&3lA#ZF3]-oTu6DfDL:%?`+B#"
"P+.#M5kHQ#[MH?=Zx3`-:MU,DJI%1Depqx.?N+$6jq_H-$u-20LW=/1?ECG)k]2-Fk8xdD5/?v$7d,g)Ooq29#$oP'@iq29'Nt2(kR.,)RbjhF/cs+&]9xr$:af)-=Z<b$/_93_:RbaZ"
"0A.I%hYIG)'Ml8&(lgWh5dc'&`Bxjkc&QM'[vjJ250RL%,DSfLk2@a$IR`YZ]'Js-#<er8f[b]uV0t`:_He'P&sd<At+P:vosqFrfh88@lVbVIYY/^#6Jt2_b?wu#n@BP8dV(T.Rk.j0"
"FE#hLqFeB&B?Xb+6=G##<C`p7/WguA;M)h$$<oO(c<_=%]J]t9DVLd#_fR0?*peA##hB#Z6unf(wem;-&oA0%$WDm/$2xUZ6x->D>Vl`%UfUV$`Zt(3=+,<?@9L.;VbGWgRakA#rCtM("
"L/?<.t#G5&ar6S#Wkf1Q9OV'Q=OcYu/_X:dMpx;12(iZ#tg1$#Uqn%#*[C&&It:2_O$0;%GYu`m#XN7%PmXb+B(2C=Nx(d*2wkD+[Fqc$5Tum8.JZ*7stm;-?^r2%xs+F%hc[lD2-;hL"
"43DhLh?]X$R:SC#JX@<-eCD9.R$s8.Tq.<-cM`2%YEC]A5h[/&eNAW-HDewpG]/wp4i:$^-#owpcv52'KWOs-5Wr39.K8p&&%s299+>2_Y4dgb1M9nfa$Ct_-t/3M0e5RG:l=>5PTe1O"
"F/bs>Q4n0#wWj-$N#no@+duoJn)`O0OZc6#t5@GrA:I<?;$%+Qf:/w>9&cZeN@wX$snm2&N,q%=g;K/bf&QJ(sni&&2AL/b/;<>5[2p;-DB$l$*exb%SU*oLb?[Y#[&+##-qN8%>6cf("
"K'#7#9Mc##Wk.j0e*ofLvC&L('&[6#e]Z6#)pYZ73?rHMW#@68,/sF55/G$M4D?##aY4a*dO7<-`Yw#%wh*<8Zn,/CwitA#]=:fu)RU/)8&S^$?q?YY7@[777>?p.gdl>7sjBRBP*#Uh"
"+e&RFr?MfL1H$##wk.l#k#ffLQDW$#eog7`*3*Z$UNt;-+ggo%_)Rnr0w_)Ndo$q7F+4m'Ll)ZS3lj+&WbD>#@+r;-m$s_:WF9/`S3N%&(1BjKBSK/)f8$K:iB.QK=gcI3S.t;&iAB&V"
"'?8Cu<*WTBRVpw^5ntgXtMr?`SjlQW#$B$J7)>$M*Ls$#D/Y`%X&u;-E_CH-r^Nn%_Z4I>-k1HMZ>;-2?tC$#,[b6#00i';KkU?%G2G7%_U7=-h5_S-NDk^%;-Xj&Hb3D<27$9gW2Z6#"
"VPY29>X1*4Lue;%<]E%$IQx;-xm(5/M;(4rO4eKuf[XL8bt0'#%/5##7_ajLK21M<vNsd*De*<--PvD-`aV&.@jcuG>7bi_@ut>$8FA'-#5E/%o?Ka<U242_vA9S%+V9d28ax9.Nw`FG"
"n&AI#%5iUd9iLq;=(1(#,uQ8%l-so%oK?]OwR?.2v/'ug$7$c*7Sca*^sJb*&1&<-XV_@-V6F,%6sC_&'EC_&;SEfOflEv%`K=X-91:0*G6339m)0K24uv9.2H9N(:C8R/rYBKCTN/]$"
"fY1U^bVc>ummlbu2h1ZuX@6iN(Y;m8]j/<R-l68%OpXrH)L/W-5V-F%Kqda*N^6O0;Ul##8$cJ(Vu>$MpmPW-R^P7A>$G?.[w2$#uCW/%FhG&#kP19.u).GrYs?Z-Uit/MDr:*%je$-D"
"$4B>5v$@l$UAkI#$ZdpL4D?uu2+iZ#/fOM-+=NM-YiHjTal@dDlJ20Z4mJ)NY:cqE,tG5&uTff.tl=;$(DNfLU-K7NU;W$#Dpi='JO_5+3-e%O0G[aN@x/$P5o#p%V2x,MWQ%f$Erx^6"
".AXmfI;u/(f(jmfV,5<-.,Wc9s:&Fe2eHTGmE4W-1ob?g0P-)?0P6<-<vYH0$:E=_uP_3_Ix@=Bmwi&M%w?h%pVGYGo:Z9MUQD#$%<YK:iM0/`@`nM.[k.j09)N:)F1P>gEMrP-LJ7m-"
"l9qFZ9I_P8n<3t_P`9<%fV(U^_%mW-fcoLawXk[(u9#7#lPQe%/^C_&Q<6XL1Wc'&4gu'&;C-L,Dx>,Mq.Q=(@,#^?=[u##OPo71W&sS_>3#O-&%_%%?kaX_.<RK<TA(b?7R/rmajGw="
"I'L#-v(IM0%5YY#&>uu#Hn?DE$_Oa=ml9-2Jkw[>Q*mRAxO?\?$-0A*``7>'],7e,Xg%4a*t,us-N^io7S*?v$c0XmU]sdh2$t@X-2PP8.NEHH3k2EIEK'H#<XPE2'$^-DWB.)m/eB9(/"
"aNc##Xe?UN]8SRN3j1(&p=mYPpd:E%XC,B#^&gGNx2-uum+XhN,RwtLX-m9%=vwQN<W2>5.-Qq7pLkM(0ov<-2kw6/v<e._9.`*O:xoF-:4K2`D7GG-#7<Y$-EWSSn$W296b9dOY9W$#"
"a2>*v_Dv6#+q8=-fDhh$sKB;%AU)m(*0(30Aa+/(6=G##;aEK3J^nO('uaO:SEIgWO0;U:;,_^#5W7H#e:EN2K=6##r3]5/fg1$#:xFx8sk%32H0Iq7-Xti_iQ3dX5E[aNF$7q7o*2jr"
"2mu,2d@san:,#^?pRd;-+V8g%R;Tu&f4k$%@/NF3EDt_$=;oRedVB7D@Uvx;U5I5&$V-s$ToeV9?.+)8ol9#v+U`k#0[@XC_UD(=Ek$VUjGv/(viA/&bni;-pbB%%d@4H9-;?v$/xF&#"
"^F$T@kfB#$fn4T%cv[O(HotM((?(B#LCWLD#'U:dA7b7gA=g*>x`5O##K*##U=.<-s*;E'ZO9Y]%4pfL35pfL3klgL2#*$#ZTE$M%JH##ZbnJ:x+$k_)M:;$MARh(uT95&KWo;-&fpJ&"
"3jc0:v&;Z@Q_@f$3u#UT>[#-&Fr#j<[>d6#sLiRq/klgL;7bj$g7x`=SwlG*>'Wm.KG4HGJ60KO5_]-BvkK+l%.gfL]Imu>?rDGWqk>,M$LBK%w4K#$T*f9rip2:0,iaj$Bmk297CgOl"
"Y4f2To$=F3frULl1LF(@oZ51l9AhrAKXa(ZHjU6=BA0j(O1@<-1j?E&)D`K_7(VV$0W95&SrBs%4$8p&;QkM(J(O&=-$9fbD7+S&@KLj0D0`$#74i$#aPZ6#U<c,;M6;'oUY>>#D0kJ)"
"?n<j(-.^('KR3To52YL<#f`oO<&io093aE4F>2>N+x:a%?w)@IU['X<HIF&#l`(X-Ex'@Il=Xa*SP-<-r4O#/+jnlf?n:$#%kEH;rw'^##?UH;[8^8:Odb`<;XV8&05+r&`gpl&(ewP'"
"eTo'H?ojZ8mtEK;F,$%ddbJo@:BPd'ajGw=ZUG19jmUNr5M@j0j?,ipIq^4fb?wu#i']A5h@>T@4*VO)g5Z6#V8>[0qsqFrD&0J3*R4S9?=Kk1=k<.=Yie_-hK5MTiX#T%2HAqD1a#Ak"
"&nSP&EQ(,)H9s3)-)olffAO,2kkp`jA+x+2?fOI#8`U[McMd6#/6@Grat[fL,Km/(r8-eMSTeEN?dRa*7pG<-YBX,%qkv;-PJj-@_VrS&D_SH;$Vfn1_G.^$0Zu4MTC=R-BR1H-fo-A-"
"6s08%;#l/G/qugL1w(hL'RGgLEP'nfvlLZ-Uokl869HZ$_:8u.'3CW-vrZ:d*bMo.$*U:d_Wl4AO?'#5Z_d@:x(WTB8`a.9jfOnEvqWW8Ted##^%;V;573Ec*-sB%V,4kO>s7'f=lu.:"
"IVX&#m)TEYK4$##,lls-K`m`*P?0q.13pL_gMo_mXReu'@he;-T,rx$[<=8%r@_-'-j5++Y^fw#+XpU/L+fC#&6aJfqG4HG$if1B>_3#d%=epLFsJfL?@/GVT*sr$DuRQBlf0-2a#x+2"
"Sdx;-Yp6:&iaD[]%g3mfWjf;-Ps7j%<Fdp'1/V/s':>GMv5sY$F>/GrWtRP/JO@X-Zp@+4>+8MDRkd1B1FiT#*;Shu'TMkuNaLd=%8V'#Gx33.?Oc&8#=>2_Yo]E[1dN&`L#4[9-9e,="
"mxAW&9a9<-Oln$8W(AZ7=n^=%WwWUEFUK1FM0CZ7JJI0B7#1<-[C//.[GpX:4ug>$?VBjB7NF&#)iBdOuMcl&1xB2_#hd--HjTw0&M*d?.`S,&@OU2_J%`K_QD/B#hHho7PU;b5g+=a*"
"7s(9.#07Gr=XWEl@5RI/3eC)=l>%iN`KdY#GpX68,b^/)ve&Kjg2k]FG]gJ)RPLx&P-;2_Bo-:(8M[9R;Uo^$SK@,M_(,@MXg(HM@(FmflakgLlStaEM>HZ$LBN1)?oNK1$PNo@PG_Jf"
"43m1;c26_f,WeT#7$r5%vrIfLt2J5?Mp@T&vYKlSP#Y296kR5'&65T.7=G##qE4u$rJ8j_-MYY#rop;-x(#S.'<IGr1hs8./3pL_xi]DZqB/S?2bb4k`DQ6/P;J#=Cq>iN9m$';7D_B#"
"F.U'#5f1$#ifW-2%a:%G.eu_Fk?R=H?+g2`(nIQ%/$x;6<a1T/`:r<DT`1GV-I4HG5_X:dh0c1BQ$?-#TdY[$Bfv]5$En`F4592_;MQg$ESI0c<D5b*x,5q7`WROXB=`3F*KEk8[MV8&"
">X*W-1w<L#IgUD3wov6W8eF(@hcmh-1P[6W0pg2(a()(6[@ib8_1mq9=O$29f7-B8g;?YUA0bj9Ele$ThgAQLY>R#%p@[V84$*%$#)P:vW(+v55FNP&h0$AOs/968X.$Z$?7.<-aj9-%"
"`HXS%oGqa6N'Qv2OOSd;'CvV%_px58K:?Z$b+61MFY5`%Vif1Bo[)euk:(4ro).GV$4B>5S:hh$;w3<-t2il-b</E%J2$#>E]gJ)j(`s-Or2a*nWXm8.=lUIepF&#j&.Y%c>P78DB5s."
"4nE<-9*tJ/)Jp551r)lLt-TH#&jem->8oF5]Ej2M2B>,2DAh;-$`Ys-AV>$MdE?##cmf;-^?19MYddh2WKt;-d;c7%)fmxFMg2_sBDLF%I;VjTM]p6D,`/+%`88C#)Xq7[42qo%M,@D*"
"<kP/Fjfv6#9GY##`k.j0lNOgLIHjj92&16;gMZ6#LTY6#kOs6#+hY[.3r+@5rvaB-wVq-%2,.6M)F5gL%Ld_FwBg?/fuN$%QpXb+L*0:@NA0j(-WCW-#Zt5V`2Z6#TMYD%V1ns-M%pUJ"
"c.,H3&aCD3#s+Z5>)IL47$[:Z?`&5:jmdI3s]Gpucp1tD]?%+Ms^Zi9*w%)X1krS&@I])+o`l2b`Gv6#mK-T-v83U-O(Ci9ig;r7:K=2_9n`Qj&(ZQs8]#b[nLwM0IrC$#6r+@5kZbgL"
"XH'cjm(*j$0U2Rsw;b)N*W..M,jeeMtaYgLiauGMR@VhL&.VHM'.gfL.rJfL]5Z6#+e,`-]FJgE9^.iL>r[.2#J>9';a&b*GoAa3Ur-14A&lL^?`&5:57_F4iFACuxhPT%06a9DJJE`W"
"42qo%QDw%+fE'dta9N$##u>q7YRoP',]r;-'6^S%3#bo7[-D)+brGQ'82e4_D&Us.)=e._U9RKu8#(<-`rMsB*;nf(#P3uf8E`hL63DhL'Fv6#H.<U.PZc6#;@Bk$]4IW-f8ZMXmn`:8"
"A?e^5Mj1tD4h4i^J4WQ/a*54U1Al[tsn5_#3cFfCUlI>5hnqZ^>CgX]2pw^$4Qg;-60SS9SJkM(okCs%UuqN9p:t)#1#2-2O5IwK:,#^?Jmp5/]Os6#vX#68P=XM_9pqgEouId)Df4*G"
"g6-jBi,bTGvipW&dnb1B]R4k#jW]Y#I/QlJD-A20s41T&?/uK*@sR+QtARlfP-F<-tH;-D2(-Z$BLFR-Zj1x$J8aEe?jVEe35M]JkPv6#,5>##/bM2B%)fJ3Jl*F3:<Xq.k1;jC,f>>5"
":4Jdg4MwuMd_/@fwX15/',Guum>q*8*m#0))m$7#2iE/%m+`5/[k.j0mZbgLX)(E<sjBj_=Rno%f@/:)AQ$O_Fn&F,D$TT<C;:CIpo<v%^EXS%t4Jr)37ih&'IPd2'C;rBXK(Xg?ZJt<"
"VrCrT(wj8K(C[^90.UB#&8YY#?Nl(WiUQ,31F#W-9#<eFVIO5A(j;r71]]2+nOpn$d62N('6ktej6Ip#Th/W-S3n0#0ipU#vNc##=(V$#;96I$]JD(=k*$Z$:Pm;-WcTfbFWO`<[KvV%"
"@`Pa*Bo^<?jOV8&]9OX-r$-32fj%-Drp7p&_G1W-d0GX]8HAX-Pv@+4@TIg)uoZ:d)X2S.VJrTfWKeAVeQ1GV7VxPh^OLt_#BQe%L(l]GHEf;-'7Q2VcUf<?h2FM_p3dKs6Z'k&8NJa*"
"mp4KCYN@`]*UhA#Isqp.hbtM(q+qcHw*>(NW.[^&j_q,D$F>;6^YW7A^d)<%JB&>Ga4NZ-Q]uw@E?^<p^gHN+`B=8%MsUd,mIka*Ig0<-A`iJsxl9ppGa^JfPIk6D5h`,M<Toq*H&lb*"
"/&#>?bE=KN^]4((JEWa*0@Yg1w).GrYc`B#$olV-B0;hL%4qW&P1B>5LIS:d0G4JEg/0E%k1Fa*F?Y1M-).m/.3dNu'xL?#vRgoLv@'s0'Y$s$hR;/1[$ai04m^m8;#sR8TWMs%LhgWh"
"c_?^?0`jJ2ZN/i)6KId)m_G)4Tg'MDJCJtTMtYOEe3kj7dF8<Ede&gLWWHuup[ik#^(V$#E;[A-Rib4%n6jqKlCba*B70$>u4xT(k.F_$j/M*McG3]-%3^)4[U9)N(^@`a]h]0GMn7Il"
"4&wY[gq@T.9f1$#:=jb$NiDE,Ljog:g5=2_;ktv.b>d/(Txb?-n$I)%2Hk,D-X:5iQIH##H5[q.+wZ)4.q3L#IotM(j0AO#uMot#N.KNEdaV:db#0I$;:M)(K6$]>@W*CR7RGgLr^[`*"
"l9oX-3?=r7j:vGE$if1BiZs;-7HuG-`c+sL;#TfLPXZY#7l1$#)Zkf*hd)RJk]Z;%nesqDGt@X-5km9DbPL8%+)sE-cXD6Mmo7p%R_-GMnJvLpBoalAv%Afq+fMSI%jO5/WJa`NNSvM'"
"EEqfL^@CGi^slA4/nYSeffNs6#>ZG`D82Z>qo,g_=E?H):;R)W7>PT.PX5ZYYtRN0&%d#P])9$#S'ksH<bV#u7Y$$GJHJ$#AktmJP0RasM_N<H*iYas-(pmoSFRBkH%p6AgE)[Y/f;=$"
"NLg$5bjl6J`mlBb;etn&CZDU@<+PhL?cLn]Dd9bj*6PO0Ilu*EEBv<dmA>CF--7CXc6m0q*tJ7/*TDIVd0=o/'WXU[%;R=HSIn7/*,XOp7f.]GBubOp-Uu=?1``]#IGp1C^@rIiT?o7]"
"Bxg%Y7LloJrZ9p/7c.2_3)?,En(Lv6O%iV[2<u8/[r#QBebgVn/2;p]l=_d*#rsp/d`9WeKx?ds%>nj:I]hvZeV6KiuQvd3*qkdE)l+X%DCvjL7SeEFi0e9A5jT)NUQWA1)t4N1m9hZ1"
"56cj1[R?w16e?D2&_0;2d'6O2xbP(3[,#v2dW;13(ou_3gdBv3rlqk3(2,?4av`54lV4J49ePc4:c:<572&U5,FgJ5bpRa5B$O:6.MhK6Yk8F6L(WX6PLAu6OcON7RRYC7AeLW76)Si7"
"dL1s7U*^+8If478av2%$a+,##v-###X:':#;1%wuWSGs-,&$&Ml/Twumm:$#l`53#7;G##vAg;-)YGs-bWn#M/XlGM0_uGM+e(HM,k1HM-q:HM.wCHM/'MHM0-VHM13`HM29iHM3?rHM"
"4E%IM5K.IM6Q7IM7W@IM8^IIM9dRIMcpS%#=T]F-AlG<-=Gg;-AGg;-CGg;-DGg;-EGg;-FGg;-GGg;-OGg;-VGg;-WGg;-XGg;-YGg;-ZGg;-[Gg;-]Gg;-^Gg;-_Gg;-`Gg;-aGg;-"
"dYGs-TS3rL`it)#8Bg;-sL`t-+JMmLmsANM&,C*#'gG<-%``=-mYGs-7crmLMT-+#(Bg;-+M`t-m(trL%slOM(/2PM#5;PM$;DPM%AMPM)YrPM*`%QM,l7QM-r@QM.xIQM/(SQM0.]QM"
"14fQM2:oQM3@xQMe'm.#vs%'.9:3jL>-1SMNEUSMDQhSMEWqSMF^$TMGd-TMHj6TMIp?TMJvHTMPD*UMQJ3UMSVEUMUcWUMViaUMWojUMY%'VMZ+0VM[19VM^=KVMwJ^VMgOgVMdb,WM"
"fn>WMgtGWMh$QWMi*ZWM==e3#*EHL-rmG<-oZGs-BT:xL%O;XMvTDXMqZMXMraVXMsg`XMtmiXMusrXMv#&YM#6AYM%BSYM'NfYM-sFZM/)YZM0/cZM2;uZM3A([M6SC[M9f_[M:lh[M"
";rq[M<x$]M>.7]MCLe]MDRn]MEXw]MHk<^MIqE^MJwN^M`Jd`MguMaMh%WaMi+aaMj1jaMk7saMl=&bMoOAbMpUJbMoIs*MaWs$#PiE9#Ck8g1o._'#[xL$#h1%wud&]NMj)9nLZAm6#"
"mSGs-DJxnLaOgVM'6*,#.#)t-ICCpLxEu9#+TGs-FhNrL(kU:#lg(T.vji4#RdF?-;AX7/?Fluu5J'%MIMI&M]H&wun@r*Ma%buL`^Jwu><w0#7,%5JZ/Pb%-x<2C9___&UF/2'%J]R*"
"M`qr$L6SR*uGE-ZX.^R*B'&F.bVm_&+QC_&o(n_&,TC_&&Pn_&Ki0wg3xn_&mA8>,=Kp_&`qfi'ZMq_&auo.Cjuh_&n8W]+#Nl_&2gC_&^Jm_&3jC_&#Gn_&4mC_&>Co_&m$02'V#'v#"
"1:<p%L8L>dGgp_&cg;A+fhn_&U@jl&*bo_&uRDM060p_&B'&F.)Zq_&gs;A+%Mi_&,TC_&]Fj_&M0gx=Y?k_&4HMY5X=n_&oMSY,=Bp_&pRf:d[Gq_&3-6A4$Io_&2gC_&wAq_&536A4"
";4j_&4mC_&`'lZ8DX=gG&>.FHMeZ<0,Beh2Sp'$Jk+_aHC0En:$w[:C8];MF*)-p84cI/Grv.UCIe0@-^meF-1tR%H9CM*H,,lVC>sUJDb3Mf5q_[DIc@_KOWZwgF#fVI=fZLB-_fjx7"
"nVIRC)S;2FZa@#HxTVo*Bc-_>->hoDRB*g273IL2X%u4:6uiiFuwsfD8ESE-%O;9CuicdG/iCrCcV0j11'12,g2<$8X.F/2,lo/3V-DP8XhdxFeBEYGIYo+DUw%;HlBel/Zl,20Z8#-3"
"/pYc28xd'&I1He-gWO`<Ok@VHwV_w'6HXf:Qf8JCKMs.Cu:k`Fr+ODF^geM1cU+p84+S5Bq4Dk=4bf'&OO)F.'NCk=cKm3+@Q)L59e/F%T3.#H:IXMC0+$^GGsXw0,Hi+MvHII-(jj#."
"e,KkL>?1sL5@1sLU,O?S-s%qL8)Z.#dUG+#=ae2./V`mLG6n+#u$),#pF`t-:I=OM1A]qLF)C4NMB;/#G=T5T/$B>-lU^C-A]AN-QGuG-&&kB->)-h--C<L##sW2:5u._JlMQq2f.Be6"
"H`%@'$JI5BxbG>HWGD2CJaD)FhgF_&D#w9)qcSfCY@_,F%;Zt77W0h?+^;J8A.P/2:*%iVH5YY#vC58.ac$)3CkPJ$Aj+###3]'/N.]OT][]OT6KQm8gAP##%i8*#YuJ*#^+^*#b7p*#"
"fC,+#jO>+#n[P+#rhc+#vtu+#$+2,#(7D,#,CV,#0Oi,#?G.%#NR@%#R_R%#G*WgZsr$JRv3@;$iklr-0u68%Y2oFi0`(v#>tJM':[jl&urhi'7NZlANmRV-NCt1BI>x=P2lC;$FNcf("
"QcSY,-i+87O0do7Cj4PS.poCj36S%k9ZOxkucUxb%fs@X?,WuYi1r@b$3g:mgc>c`Mq&Sn8h?YPLS-JUWW)AOD<6fqK/p@kt)7VZ`5Quc>vViBcGx:QS(f7eQfi:d%#bxO[cPlSpP,MT"
"Wd:ip[>XrQh6>]XGd8SRso'J_B`Q%bKb%G`Lq[(aave1^:fGi^vnMiT4;0P]:2d7nrWI]FFdn(EM(1DEDf_S%eArIq<Q)PfPn?VQV*Frmpsa+`L.%p%m#)Sek+f4f&r1AF]Hx7ITuSfC"
"sOFlfOuo7[b?;fh#+$JhxUwOo-C.>G['EYGcT]rH>Vv4J2-^oIrVq1KulQiKx%n.Ls;>SIox3creTqFrTUxLpaCY+i0s3S[m3io.,=*Yl1MLM0ud*20mj?P;S.1VC(3f:C$]eFHpg`9C"
"[5vsBx/(G$kwViF>#8kEv@+WH$XB*5tdejB$nV=B?.+@0d>0K2.-;*#-Um$$-MYY#4]>>#&D(v#d.Wt(vPSY,P[?>#Ner*>:[_>$,oF&#7@cA#'r0B#*>;MF.uF&#J-;B#)AYY#+7`T."
".;cY#TExT%%7_c)Dk(5894nrH&>afL>$RYPV`CMToE5AX1,'5]Ihn(abM`rd$4QfhcD'v#i5-A4Tw=rdv8f7R*]qr$F-D]Oe$wA>(3,>>5)A5^_2,F%&hj-$'kj-$(nj-$)qj-$*tj-$"
"+wj-$,$k-$nh-XJ2-;hL43DhL19MhL2?VhL3E`hL4KihL5QrhLcvS%#vR-iL=j@iL=,fiL?8xiL@>+jLAD4jLBJ=jLCPFjLK+:kLRU$lLS[-lLTb6lLUh?lLVnHlLWtQlLX$[lLY*elL"
"Z0nlL[6wlL]<*mL^B3mL7nk)#(Ws)##x26.>PVmLeaamLI1C*#BcrmL)$0nLj5KnLGZ-+#SIxnLN#[+#nU4oLxrPoLuxYoLv(doLw.moL%G;pL&MDpL(YVpL)``pL*fipL+lrpL,r%qL"
"-x.qL.(8qL/.AqLi9m.#7st.#:fNrLF3urL@?1sLAE:sLBKCsLCQLsLDWUsLE^_sLFdhsLL2ItLM8RtLODetLQPwtLRV*uLS]3uLUiEuLVoNuLWuWuLY+kuLN8'vLa=0vL`OKvLb[^vL"
"cbgvLdhpvLen#wLg$6wL<-?wLm0HwL@XE0vC3YwLpBdwLmHmwLnNvwLoT)xLpZ2xLqa;xLrgDxLu#axLw/sxL#</#M)af#M+mx#M,s+$M.)>$M//G$M2Ac$M5S(%M6Y1%M7`:%M8fC%M"
":rU%M?:.&M@@7&MAF@&MDX[&ME_e&MFen&M[8-)Mccm)Mdiv)Meo)*Mfu2*Mg%<*Mh+E*Mk=a*MlCj*MmIs*MLC-##PiE9#@eNYdL'%Q0d5Ke$-MxFM0Pg;-><)=-qHg;-o#^GM5C&wu"
"u;)=-OIg;-QIg;-UIg;-LFq8/U7>###>H&M&sx8#WV*9#*(MT.rJIwuAk#E4@Sl##?.`$#JL7%#.^Q(#_1g*#@IxnLb/b,#4[%-#1'Z3#w,85#a@r*M'S$##9l:$#1####(PUV$e&YAr"
"1$###";