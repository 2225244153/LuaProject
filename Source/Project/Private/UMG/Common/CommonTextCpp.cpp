// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Common/CommonTextCpp.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/ScaleBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/ScaleBoxSlot.h"
#include "Kismet/KismetMathLibrary.h"

void UCommonTextCpp::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UCommonTextCpp::PreConstructEvent()
{
	LeadingCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ScaleBox_Leading);
	BackwardCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(TextBlock_Backup);

	SetText(Text);
}

void UCommonTextCpp::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCommonTextCpp::NativeDestruct()
{
	Super::NativeDestruct();
	ClearTimer();
}

void UCommonTextCpp::ExchangeLeadingText()
{
	bIsInitialLeading = not bIsInitialLeading;
}

FString UCommonTextCpp::GetTextDisPlayType() const
{
	if (const float TextSizeDifference = DesiredTextSize.X - DisplayAreaSize.X ; TextSizeDifference < 0.0f)
	{
		return FString("Normal");
	}
	else if (bIsAutoScaleEnabled)
	{
		return FString("AutoScale");
	}
	else if (bIsScrollBackAndForthEnabled)
	{
		return FString("ScrollBackAndForth");
	}
	else if (bIsLoopScrollEnabled)
	{
		return FString("LoopScroll");
	}
	else
	{
		return FString("Normal");
	}
	
}

UCanvasPanelSlot* UCommonTextCpp::GetMainWidgetAsCanvasSlot() const
{
	return UWidgetLayoutLibrary::SlotAsCanvasSlot(ScaleBox_Leading);
}

void UCommonTextCpp::AdjustInitialLayout(const FString& TextDisplayType) const
{
	UCanvasPanelSlot* CanvasPanelSlot = GetMainWidgetAsCanvasSlot();
	if (TextDisplayType == FString("LoopScroll"))
	{
		CanvasPanelSlot->SetAnchors(FAnchors(1.0f,0.5f,1.0f,0.5f));
		CanvasPanelSlot->SetAutoSize(true);
		if (TextJustification == ETextJustify::Left)
		{
			CanvasPanelSlot->SetPosition(FVector2D((0 - DisplayAreaSize.X),0));
		}
		else
		{
			CanvasPanelSlot->SetPosition(FVector2D(0,0));
		}
		CanvasPanelSlot->SetAlignment(FVector2D(0.0f,0.5f));
	}
	else if (TextDisplayType == FString("ScrollBackAndForth"))
	{
		CanvasPanelSlot->SetAnchors(FAnchors(0.5f,0.5f,0.5f,0.5f));
		CanvasPanelSlot->SetAutoSize(true);
		CanvasPanelSlot->SetPosition(FVector2D(0,0));
		CanvasPanelSlot->SetAlignment(FVector2D(0.5f,0.5f));
	}
	else if (TextDisplayType == FString("AutoScale"))
	{
		CanvasPanelSlot->SetAnchors(FAnchors(0.0f,0.0f,1.0f,1.0f));
		CanvasPanelSlot->SetAutoSize(false);
		CanvasPanelSlot->SetOffsets(FMargin(0.0f,0.0f,0.0f,0.0f));
		CanvasPanelSlot->SetPosition(FVector2D(0,0));
		CanvasPanelSlot->SetAlignment(FVector2D(0.5f,0.5f));
	}
	else if (TextDisplayType == FString("Normal"))
	{
		CanvasPanelSlot->SetAnchors(FAnchors(0.5f,0.5f,0.5f,0.5f));
		CanvasPanelSlot->SetAutoSize(true);
		CanvasPanelSlot->SetPosition(FVector2D(0,0));
		CanvasPanelSlot->SetAlignment(FVector2D(0.5f,0.5f));
	}
}

FVector2D UCommonTextCpp::GetCalculateLocalSize() const
{
	return GetCachedGeometry().GetLocalSize();
}

float UCommonTextCpp::GetTextDesireSizeWidth() const
{
	return TextBlock_Backup->GetDesiredSize().X;
}

void UCommonTextCpp::GetActualLeadingAndBackwardText(UCanvasPanelSlot*& OutBackwardCanvasSlot,
	UCanvasPanelSlot*& OutLeadingCanvasSlot) const
{
	if (bIsInitialLeading)
	{
		OutBackwardCanvasSlot = BackwardCanvasSlot;
		OutLeadingCanvasSlot = LeadingCanvasSlot;
	}
	else
	{
		OutBackwardCanvasSlot = LeadingCanvasSlot;
		OutLeadingCanvasSlot = BackwardCanvasSlot;
	}
}

void UCommonTextCpp::SetText(const FText& InText)
{
	TextBlock_Leading->SetText(InText);
	TextBlock_Backup->SetText(InText);

	Refresh();
}

void UCommonTextCpp::ClearTimer()
{
	if (UKismetSystemLibrary::K2_IsValidTimerHandle(LeadingTimer))
	{
		UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(GetWorld(),LeadingTimer);
	}
	if (UKismetSystemLibrary::K2_IsValidTimerHandle(BackwardTimer))
	{
		UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(GetWorld(),BackwardTimer);
	}
}

void UCommonTextCpp::Refresh() 
{
	TextBlock_Leading->SetShadowOffset(InShadowOffset);
	TextBlock_Backup->SetShadowColorAndOpacity(InShadowColorAndOpacity);
	
	TextBlock_Leading->SetFont(InFontInfo);
	TextBlock_Backup->SetFont(InFontInfo);

	TextBlock_Leading->SetColorAndOpacity(TextColor);
	TextBlock_Backup->SetColorAndOpacity(TextColor);

	ClearTimer();

	ForceLayoutPrepass();

	DesiredTextSize = TextBlock_Backup->GetDesiredSize();

	InitSizeLimitLayout(bIsTextAreaSizeLimit);

	TextBlock_Backup->SetVisibility(ESlateVisibility::Hidden);

	
	if (FString const Str = GetTextDisPlayType();Str == FString("LoopScroll"))
	{
		if (bIsLoopScrollEnabled)
		{
			TextBlock_Backup->SetVisibility(ESlateVisibility::Visible);
			AdjustInitialLayout(Str);
			TriggerLeadingTextScrolling();
		}
	}
	else if (Str == FString("ScrollBackAndForth"))
	{
		if (bIsScrollBackAndForthEnabled)
		{
			AdjustInitialLayout(Str);
			TriggerLeadingTextScrolling();
		}
	}
	else if (Str == FString("AutoScale"))
	{
		if (bIsAutoScaleEnabled)
		{
			AdjustInitialLayout(Str);
		}
	}
	else if (Str == FString("Normal"))
	{
		AdjustInitialLayout(Str);
	}
	SetTextJustification(TextJustification);
}

void UCommonTextCpp::InitSizeLimitLayout(bool const IsTextAreaSizeLimit)
{
	if (IsTextAreaSizeLimit)
	{
		if (DesiredTextSize.X < DisplayAreaSize.X and bTreatTextDSAsMinDS)
		{
			ContainerAreaSize.X = bApplyItalicOffset ? 0.0f : ItalicOffset;
			ContainerAreaSize.Y = DisplayAreaSize.Y;
		}
		else
		{
			ContainerAreaSize = DisplayAreaSize;
		}
		if (UCanvasPanelSlot* DisplayAreaCanvasSlot =  UWidgetLayoutLibrary::SlotAsCanvasSlot(DisplayAreaCanvas))
		{
			DisplayAreaCanvasSlot->SetSize(ContainerAreaSize);
			DisplayAreaCanvasSlot->SetAnchors(FAnchors(0.5f,0.5f,0.5f,0.5f));
		}
	}
}

void UCommonTextCpp::TriggerLeadingTextScrolling()
{
	GetWorld()->GetTimerManager().SetTimer(LeadingTimer,this,&UCommonTextCpp::Leading,ScrollingFrequency,true);
	Leading();
}

void UCommonTextCpp::Leading()
{
	GetActualLeadingAndBackwardText(BackwardCanvasSlot,LeadingCanvasSlot);
	FVector2D const NewPosition =  LeadingCanvasSlot->GetPosition() - FVector2D(ScrollingSpeed,0.0f);
	LeadingCanvasSlot->SetPosition(NewPosition);
	if (UKismetMathLibrary::NearlyEqual_FloatFloat(FMath::Abs(NewPosition.X),(LoopScrollSpace + DesiredTextSize.X), ScrollingSpeed))
	{
		TriggerBackwardTextScrolling();
	}
	if (UKismetMathLibrary::NearlyEqual_FloatFloat((DesiredTextSize.X + DisplayAreaSize.X + 20),(LoopScrollSpace + DesiredTextSize.X), ScrollingSpeed))
	{
		ClearTimer();
		ExchangeLeadingText();
		TriggerLeadingTextScrolling();
		BackwardCanvasSlot->SetPosition(FVector2D(0.0f,0.0f));
	}
	
}

void UCommonTextCpp::SetTextJustification(TEnumAsByte<ETextJustify::Type> const InTextJustification) const
{
	if (FString const String = GetTextDisPlayType(); String == FString("AutoScale") or String == FString("LoopScroll"))
	{
		UScaleBoxSlot* TextBlockLeadingSlot =  UWidgetLayoutLibrary::SlotAsScaleBoxSlot(TextBlock_Leading);
		switch (InTextJustification)
		{
			case ETextJustify::Left:
			TextBlockLeadingSlot->SetHorizontalAlignment(HAlign_Left);
			break;
			case ETextJustify::Center:
			TextBlockLeadingSlot->SetHorizontalAlignment(HAlign_Center);
			break;
			case ETextJustify::Right:
			TextBlockLeadingSlot->SetHorizontalAlignment(HAlign_Right);
			default:
			TextBlockLeadingSlot->SetHorizontalAlignment(HAlign_Left);
		}
	}
	else
	{
		UCanvasPanelSlot* ScaleBoxLeadingSlot =  UWidgetLayoutLibrary::SlotAsCanvasSlot(TextBlock_Leading);
		switch (InTextJustification)
		{
		
			case ETextJustify::Left:
			ScaleBoxLeadingSlot->SetAnchors(FAnchors(0.0f,0.5f,0.0f,0.5f));
			ScaleBoxLeadingSlot->SetAlignment(FVector2D(0.0f,0.5f));
			ScaleBoxLeadingSlot->SetPosition(FVector2D(0.0f,0.0f));
			case ETextJustify::Right:
			ScaleBoxLeadingSlot->SetAnchors(FAnchors(1.0f,0.5f,1.0f,0.5f));
			ScaleBoxLeadingSlot->SetAlignment(FVector2D(1.0f,0.5f));
			ScaleBoxLeadingSlot->SetPosition(FVector2D(0.0f,0.0f));
			default:
			ScaleBoxLeadingSlot->SetAnchors(FAnchors(0.0f,0.5f,0.0f,0.5f));
			ScaleBoxLeadingSlot->SetAlignment(FVector2D(0.0f,0.5f));
			ScaleBoxLeadingSlot->SetPosition(FVector2D(0.0f,0.0f));
		}
	}
}

void UCommonTextCpp::TriggerBackwardTextScrolling()
{
	GetWorld()->GetTimerManager().SetTimer(BackwardTimer,this,&UCommonTextCpp::BackScrolling,ScrollingFrequency,true);
}

void UCommonTextCpp::BackScrolling()
{
	GetActualLeadingAndBackwardText(BackwardCanvasSlot,LeadingCanvasSlot);
	BackwardCanvasSlot->SetPosition(BackwardCanvasSlot->GetPosition() - FVector2D(ScrollingSpeed,0.0f));
}

void UCommonTextCpp::InitScrollOffset()
{
	GetMainWidgetAsCanvasSlot()->SetPosition(FVector2D(((DesiredTextSize.X - DisplayAreaSize.X)),0.0f));
}






