// 2023 Labverso, Brazil. Imersion Test.


#include "FlamingSphere.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AFlamingSphere::AFlamingSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to 
	// improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Cria uma instância de USphereComponent que será apontada
	// por EsferaDeColisao.
	EsferaDeColisao = CreateDefaultSubobject<USphereComponent>(TEXT("Raiz"));

	// Define o tamanho do raio da esfera.
	EsferaDeColisao->InitSphereRadius(100.0f);

	// Define o nome do perdil de colisão.
	EsferaDeColisao->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	// Indica que EsferaDeColisao será o componente Raiz da hierarquia de
	// componentes.
	RootComponent = EsferaDeColisao;

	// Cria uma StaticMesh e coloca o endereço de memória deste recurso no 
	// ponteiro EsferaVisivel.
	EsferaVisual = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("Esfera"));

	// Cria um Componente de Particula e coloca o endereço de memória deste 
	// recurso no ponteiro ParticulaDeFogo.
	ParticulaDeFogo = CreateDefaultSubobject<UParticleSystemComponent>
		(TEXT("Particula de Fogo"));

	// Anexa este componente como sendo filho do componente EsferaVisual.
	ParticulaDeFogo->SetupAttachment(EsferaVisual);

	// Ativa o bool(flag) que indica que o efeito da particula deve auto
	// iniciar.
	ParticulaDeFogo->bAutoActivate = true;

	// Cria o componente TextoDeExibicao
	TextoDeExibicao = CreateDefaultSubobject<UTextRenderComponent>
		(TEXT("Texto"));

	// Anexa o componente de texto como filho de EsferaVisiual
	// (hierarquia de componentes).
	TextoDeExibicao->SetupAttachment(EsferaVisual);

	// Indica a localização do componente em relação ao "Pai" na hierarquia.
	TextoDeExibicao->SetRelativeLocation(FVector(0.f, 0.f, 110.f));

	// Alinha de forma centralizada o conteúdo do texto na horizontal.
	TextoDeExibicao->SetHorizontalAlignment(EHTA_Center);

	// Indica e Altera o tamanho da escala X e Y.
	TextoDeExibicao->SetYScale(1.f);
	TextoDeExibicao->SetXScale(1.f);

	// Inicializa um texto inicial.
	// Converte de String para FText.
	TextoDeExibicao->SetText(FText::FromString("C++ na Unreal"));

	//Coloca cor no texto de exibicao.
	TextoDeExibicao->SetTextRenderColor(FColor::Red);

	//Deixa o texto visivel.
	TextoDeExibicao->SetVisibility(true);

	// Quando uma sobreposição de atores ocorrer em cena,
	// a função OnActorBeginOverlap é acionada.
	// AddDynamic anexa a função InicioSobreposição para que ela também seja 
	// chamada quando ocorrer uma sobreposição.
	OnActorBeginOverlap.AddDynamic(this, &AFlamingSphere::InicioSobreposicao);

	OnActorEndOverlap.AddDynamic(this, &AFlamingSphere::FimSobreposicao);

	// Localiza via código a StaticMesh que usaremos 
	// no componente EsferaVisual.
	ConstructorHelpers::FObjectFinder<UStaticMesh>Esfera(TEXT(
		"StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	// Localiza via código o Material da Esfera.
	ConstructorHelpers::FObjectFinder<UMaterialInterface>Esfera_MAT(TEXT(
		"Material'/Game/StarterContent/Materials/M_Metal_Rust.M_Metal_Rust'"));
	// Localiza via código o sistema de partiulas da Esfera.
	ConstructorHelpers::FObjectFinder<UParticleSystem>EsferaEFX(TEXT(
		"ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));

	// Se todos os recursos forem iniciados com sucesso, continue.
	if (Esfera.Succeeded() && Esfera_MAT.Succeeded() && EsferaEFX.Succeeded())
	{
		// Atribui o StaticMesh da EsferaVisual com o Esfera.Object encontrado.
		EsferaVisual->SetStaticMesh(Esfera.Object);
		// Atribui o Material da EsferaVisual com o Material Encontrado pelo
		// ConstructorHelpers.
		EsferaVisual->SetMaterial(0, Esfera_MAT.Object);
		// Atribui a Efeito de Particula ao Ator.
		ParticulaDeFogo->SetTemplate(EsferaEFX.Object);

		//Atribui a localização do componente EsferaVisual.
		EsferaVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -60.f));
	}

	// Anexa este componente como sendo filho do componente Raiz
	// (EsferaDeColisao).
	EsferaVisual->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFlamingSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlamingSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlamingSphere::InicioSobreposicao(AActor* OverlappedActor,
	AActor* OtherActor)
{
	FString StringDeSaida;
	StringDeSaida = "Sobrepondo " + OtherActor->GetName() + " !";

	TextoDeExibicao->SetText(FText::FromString(StringDeSaida));
}

void AFlamingSphere::FimSobreposicao(AActor* OverlappedActor,
	AActor* OtherActor)
{
	TextoDeExibicao->SetText(FText::FromString("Parou de Sobrepor"));
}

