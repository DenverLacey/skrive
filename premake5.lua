workspace "skrive"
	configurations { "Debug", "Release" }

project "skrive"
	kind "ConsoleApp"
	language "C++"
    cppdialect "C++17"

	files {
		"src/**",
	}

	includedirs { "src" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
