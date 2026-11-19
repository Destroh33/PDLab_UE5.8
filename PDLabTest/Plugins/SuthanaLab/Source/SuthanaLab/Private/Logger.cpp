// Fill out your copyright notice in the Description page of Project Settings.


#include "Logger.h"

// Sets default values for this component's properties
ULogger::ULogger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULogger::BeginPlay()
{
	Super::BeginPlay();

	headpos = FVector::ZeroVector;
	headrot = FVector::ZeroVector;
	gazeOrigin = FVector::ZeroVector;
	gazeDirection = FVector::ZeroVector;
	fixationPoint = FVector(0.0f, 0.0f, 0.0f);

	uworldref = GetWorld();
	
}


// Called every frame
void ULogger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (logopen) {
		logTimer -= DeltaTime;
		if (logTimer <= 0.0f) {
			this->LogLine("","RTdata");
			logTimer = 1.0f / FMath::Clamp(logRate, 2.0f, 100.0f);
		}
	}
}

void ULogger::BeginDestroy() {
	Super::BeginDestroy();

	this->FinishLogger();
}

void ULogger::InitializeLogger() {
	if (!logopen) {
		FString timestamp = "";  //mm_dd_yyyy_HH_mm_ss
		std::time_t mtime = std::time(0);
		std::tm* now = std::localtime(&mtime);
		timestamp += "_" + FString::FromInt(now->tm_mon + 1) + "_";
		timestamp += FString::FromInt(now->tm_mday) + "_";
		timestamp += FString::FromInt(now->tm_year + 1900) + "_";
		timestamp += FString::FromInt(now->tm_hour) + "_";
		timestamp += FString::FromInt(now->tm_min) + "_";
		timestamp += FString::FromInt(now->tm_sec);
						
		#if PLATFORM_WINDOWS
		FString Logfilename = FPaths::ProjectDir() + "TaskLogs/" + LogName.ToString() + timestamp + ".csv";
		#elif PLATFORM_ANDROID
		FString Logfilename = FPaths::ProjectPersistentDownloadDir() + "/" + LogName.ToString() + timestamp + ".csv";
		#endif
		
		UE_LOG(LogTemp, Warning, TEXT("Logging at: %s"), *Logfilename);
		//FString Logfilename = FPaths::ProjectDir() + "Build/Android/assets/" + LogName + ".csv";
		myfile.open(std::string(TCHAR_TO_UTF8(*Logfilename)));
		logopen = true;

		std::string logheaders = "Time,DataType,headposx,headposy,headposz,headrotx,headroty,headrotz";
		logheaders += ",gazeOriginx,gazeOriginy,gazeOriginz,gazeDirectionx,gazeDirectiony,gazeDirectionz";
		logheaders += ",fixationPointx,fixationPointy,fixationPointz,interceptPointx,interceptPointy,interceptPointz";
		logheaders += ",interceptDist,interceptName";
		logheaders += ",leftEyeOriginx,leftEyeOriginy,leftEyeOriginz,leftEyeDirectionx,leftEyeDirectiony,leftEyeDirectionz";
		logheaders += ",rightEyeOriginx,rightEyeOriginy,rightEyeOriginz,rightEyeDirectionx,rightEyeDirectiony,rightEyeDirectionz";
		logheaders += ",optiposx,optiposy,optiposz,optirotx,optiroty,optirotz";
		logheaders += "," + std::string(TCHAR_TO_UTF8(*customPosName.ToString())) + "x," + std::string(TCHAR_TO_UTF8(*customPosName.ToString())) + "y," + std::string(TCHAR_TO_UTF8(*customPosName.ToString())) + "z";
		logheaders += ",leftEyeBlink,rightEyeBlink,leftPupil,rightPupil,eventMessage";
		myfile << logheaders + "\n";
	}
}
void ULogger::LogLine(FString LogLine, FString logtype) {
	if (logopen) {
		float realtimeSeconds = uworldref->GetTimeSeconds();
		
		FString line2write = "";
		line2write = FString::Printf(TEXT("%f"), realtimeSeconds);
		line2write += ","+logtype;
		line2write += ","+FString::Printf(TEXT("%f"),headpos.X)+","+ FString::Printf(TEXT("%f"),headpos.Y)+","+ FString::Printf(TEXT("%f"), headpos.Z);
		line2write += ","+ FString::Printf(TEXT("%f"), headrot.X) + "," + FString::Printf(TEXT("%f"), headrot.Y) + "," + FString::Printf(TEXT("%f"), headrot.Z);
		line2write += "," + FString::Printf(TEXT("%f"), gazeOrigin.X) + "," + FString::Printf(TEXT("%f"), gazeOrigin.Y) + "," + FString::Printf(TEXT("%f"), gazeOrigin.Z);
		line2write += "," + FString::Printf(TEXT("%f"), gazeDirection.X) + "," + FString::Printf(TEXT("%f"), gazeDirection.Y) + "," + FString::Printf(TEXT("%f"), gazeDirection.Z);
		line2write += "," + FString::Printf(TEXT("%f"), fixationPoint.X) + "," + FString::Printf(TEXT("%f"), fixationPoint.Y) + "," + FString::Printf(TEXT("%f"), fixationPoint.Z);
		line2write += "," + FString::Printf(TEXT("%f"), interceptPoint.X) + "," + FString::Printf(TEXT("%f"), interceptPoint.Y) + "," + FString::Printf(TEXT("%f"), interceptPoint.Z);

		line2write += "," + FString::Printf(TEXT("%f"), interceptDist) + "," + interceptName;

		line2write += "," + FString::Printf(TEXT("%f"), leftEyeOrigin.X) + "," + FString::Printf(TEXT("%f"), leftEyeOrigin.Y) + "," + FString::Printf(TEXT("%f"), leftEyeOrigin.Z);
		line2write += "," + FString::Printf(TEXT("%f"), leftEyeDirection.X) + "," + FString::Printf(TEXT("%f"), leftEyeDirection.Y) + "," + FString::Printf(TEXT("%f"), leftEyeDirection.Z);
		line2write += "," + FString::Printf(TEXT("%f"), rightEyeOrigin.X) + "," + FString::Printf(TEXT("%f"), rightEyeOrigin.Y) + "," + FString::Printf(TEXT("%f"), rightEyeOrigin.Z);
		line2write += "," + FString::Printf(TEXT("%f"), rightEyeDirection.X) + "," + FString::Printf(TEXT("%f"), rightEyeDirection.Y) + "," + FString::Printf(TEXT("%f"), rightEyeDirection.Z);
		line2write += "," + FString::Printf(TEXT("%f"), optipos.X) + "," + FString::Printf(TEXT("%f"), optipos.Y) + "," + FString::Printf(TEXT("%f"), optipos.Z);
		line2write += "," + FString::Printf(TEXT("%f"), optirot.X) + "," + FString::Printf(TEXT("%f"), optirot.Y) + "," + FString::Printf(TEXT("%f"), optirot.Z);

		line2write += "," + FString::Printf(TEXT("%f"), customPos.X) + "," + FString::Printf(TEXT("%f"), customPos.Y) + "," + FString::Printf(TEXT("%f"), customPos.Z);

		line2write += "," + FString::Printf(TEXT("%d"), leftEyeBlink);
		line2write += "," + FString::Printf(TEXT("%d"), rightEyeBlink);
		line2write += "," + FString::Printf(TEXT("%f"), leftPupil);
		line2write += "," + FString::Printf(TEXT("%f"), rightPupil);
		line2write += "," + LogLine;

		UE_LOG(LogTemp, Warning, TEXT("Logging: %s"), *line2write);
		myfile << std::string(TCHAR_TO_UTF8(*line2write)) + "\n";
	}
}
void ULogger::FinishLogger() {
	if (logopen) {
		myfile.close();
		logopen = false;
	}
}