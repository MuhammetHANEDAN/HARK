
#include "HEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AHEffectActor::AHEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));

}

void AHEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if(TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;
	
	/*IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(TargetActor);
	if(ASCInterface)
	{
		ASCInterface->GetAbilitySystemComponent();
	}*/

	// yukarısını yerine bu daha mantıklı
	//UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	// Bu önce actöre bakıyor interface varmı diye yoksa actorun içine findcomponentbyclass kullnaarak ASC in var olup olmadıgına bakıp döndürüyor

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(TargetASC == nullptr) return;
	check(GameplayEffectClass);
	
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this); // Bu efekti hangi actor yaptı

	// En alttaki EffectSpec i bu EffectSpecHanle ı kullanarak alacağız
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass,ActorLevel,EffectContextHandle);
	
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get()); // Dereference işlemi var * solda
	// Çünkü  FGameplayEffectSpec& bekliyor ama EffectSpecHandle.Data.Get() bize FGameplayEffectSpec* döndürüyor

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if(bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandle.Add(ActiveGameplayEffectHandle, TargetASC);
	}

	if(bDestroyOnEffectApplication && !bIsInfinite)
	{
		Destroy();
	}

	
}

void AHEffectActor::OnOverlap(AActor* TargetActor)
{
	if(TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
}

void AHEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if(TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
	if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if(!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;

		for (auto HandlePair : ActiveEffectHandle)
		{
			if(TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

		for ( FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			ActiveEffectHandle.FindAndRemoveChecked(Handle);
		}
	}
}
