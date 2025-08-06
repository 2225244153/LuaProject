// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CommonTextCpp.generated.h"

class UCanvasPanel;
class UTextBlock;
class UScaleBox;
class UCanvasPanelSlot;
/**
 * 
 */
UCLASS()
class PROJECT_API UCommonTextCpp : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
	void PreConstructEvent();

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	void ExchangeLeadingText();

	FString GetTextDisPlayType() const;

	UCanvasPanelSlot* GetMainWidgetAsCanvasSlot() const ;

	void AdjustInitialLayout(const FString& TextDisplayType) const;

	FVector2D GetCalculateLocalSize() const;

	float GetTextDesireSizeWidth() const;

	void GetActualLeadingAndBackwardText(UCanvasPanelSlot*& OutBackwardCanvasSlot,UCanvasPanelSlot*& OutLeadingCanvasSlot) const;

	void ClearTimer();
	
	void Refresh() ;
	
	void InitSizeLimitLayout(bool const IsTextAreaSizeLimit);

	void TriggerLeadingTextScrolling();

	UFUNCTION()
	void Leading();

	void SetTextJustification(TEnumAsByte<ETextJustify::Type> InTextJustification) const;

	void TriggerBackwardTextScrolling();

	UFUNCTION()
	void BackScrolling();

	void InitScrollOffset();

public:

	UPROPERTY()
	bool bIsInitialLeading = false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector2D DesiredTextSize = FVector2D(0,0);

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector2D DisplayAreaSize = FVector2D(78,37);

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bIsAutoScaleEnabled = false ;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bIsScrollBackAndForthEnabled = true;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bIsLoopScrollEnabled = false;
	
	UPROPERTY(meta=(BindWidget))
	UScaleBox* ScaleBox_Leading;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_Leading;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock_Backup;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* DisplayAreaCanvas;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<ETextJustify::Type> TextJustification;

	UPROPERTY()
	UCanvasPanelSlot* LeadingCanvasSlot;

	UPROPERTY()
	UCanvasPanelSlot* BackwardCanvasSlot;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector2D InShadowOffset = FVector2D(1.0f,1.0f);

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FLinearColor InShadowColorAndOpacity = FLinearColor(0.0f,0.0f,0.0f,0.0f);

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FSlateFontInfo InFontInfo;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FSlateColor TextColor = FSlateColor(FLinearColor::White);

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle LeadingTimer;

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle BackwardTimer;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bIsTextAreaSizeLimit = false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bTreatTextDSAsMinDS = false;

	UPROPERTY(BlueprintReadWrite)
	FVector2D ContainerAreaSize = FVector2D(0.0f,0.0f);

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bApplyItalicOffset = false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float ItalicOffset = 5.0f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float ScrollingFrequency = 0.1f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float ScrollingSpeed = 5.0f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float LoopScrollSpace = 40.0f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FText Text;
	
	float ScrollBackOffset = 5.0f;

	
	UFUNCTION()
	void SetText(const FText& InText);
	
};
