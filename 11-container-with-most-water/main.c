#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#define қазақшасөйле setlocale(LC_ALL, "kk_kz.UTF-8")
#define басты main
#define қайт return
#define аш {
#define жап }
#define егер if
#define әйтпесе else
#define болғанша while
#define үшін for
#define кетбар break
#define өтіпкет continue
#define секір goto
#define және &&
#define әлде ||
#define жә &
#define әл |
#define я ^
#define жаз printf
#define жжаз sprintf
#define фжаз fprintf
#define оқы scanf
#define фоқы fscanf
#define жоқы sscanf
#define тең =
#define теңтең ==
#define үлкен >
#define үтең >=
#define кіші <
#define ктең <=
#define қосу +
#define алу -
#define көбу *
#define бөлу /
#define қостең +=
#define алтең -=
#define көбтең *=
#define бөлтең /=
#define арттыр ++
#define азайт --
#define проц %
#define жаңажол "\n"
#define ондықПішім "%d"
#define жолПішім "%s"

#define нөл 0
#define бір 1
#define екі 2
#define үш 3
#define төрт 4
#define бес 5
#define алты 6
#define жеті 7
#define сегіз 8
#define тоғыз 9
#define он 10
#define жиырма 20
#define отыз 30
#define қырық 40
#define елу 50
#define алпыс 60
#define жетпіс 70
#define сексен 80
#define тоқсан 90
#define жүз 100
#define мың 1000
#define миллион 1000000
#define миллиард 1000000000
#define шын бір
#define жалған нөл

#define анықта typedef
#define тұрақты const
#define таңбалы signed
#define таңбасыз unsigned
#define ұзын long
#define ұзыыын long long
#define бүтін int
#define нақты float
#define дәл double
#define таңба char
#define қуыс void
анықта таңба* жол;

#define ЖИЫМ(жиым, сан) жиым[сан]
#define көлем sizeof
#define құрылым struct
#define оның ->

#define сұрыпта qsort
#define абс abs

#define АРАЛЫҚ(і, а, б) үшін(бүтін і тең а; і кіші б; і арттыр)
#define КЕРІАРАЛЫҚ(і, а, б) үшін(бүтін і тең а - 1; і үтең б; і азайт)

#define КІШІСІ(а, б) ((а) кіші (б) ? (а) : (б))
#define ҮЛКЕНІ(а, б) ((а) үлкен (б) ? (а) : (б))

#define еңҮлкенАудан maxArea
бүтін еңҮлкенАудан(бүтін* биіктіктер, бүтін сан) аш
	бүтін еүАудан тең нөл;
	бүтін *сол тең биіктіктер, *оң тең биіктіктер қосу сан алу бір;

	болғанша(сол кіші оң) аш
		бүтін ен тең оң алу сол;
		бүтін биіктік;
		егер (*сол кіші *оң) аш
			биіктік тең *сол;
			сол арттыр;
		жап
		әйтпесе аш
			биіктік тең *оң;
			оң азайт;
		жап
		бүтін аудан тең ен көбу биіктік;
		егер (аудан үлкен еүАудан)
			еүАудан тең аудан;
	жап
	
	қайт еүАудан;
жап

бүтін басты(бүтін аргСаны, жол ЖИЫМ(аргтар, )) аш
	егер (аргСаны теңтең бір) қайт бір;
	бүтін сан тең аргСаны алу бір;
	бүтін ЖИЫМ(биіктіктер, сан);
	АРАЛЫҚ(і, нөл, сан) аш
		жоқы(ЖИЫМ(аргтар, і қосу бір), ондықПішім, биіктіктер қосу і);
	жап
	жаз(ондықПішім жаңажол, еңҮлкенАудан(биіктіктер, сан));
	қайт нөл;
жап
