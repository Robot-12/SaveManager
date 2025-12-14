<div align="center">

# 💾 Save Manager for Unreal Engine 5
### A Robust & Modular Save System

![Unreal Engine 5](https://img.shields.io/badge/Unreal_Engine-5.0+-black?style=for-the-badge&logo=unrealengine)
![Status](https://img.shields.io/badge/Status-BETA-orange?style=for-the-badge)
![Author](https://img.shields.io/badge/Created_By-Robot_12-blue?style=for-the-badge)

</div>

---

## 👋 Introduction
Welcome to **Save Manager**! 🚀

This project is special to me as it marks my **very first plugin developed for Unreal Engine 5**. I created it to provide a clean, C++ based solution for handling game saves without the clutter often found in Blueprint-only solutions.

> ⚠️ **Note:** This plugin is currently in **BETA**. It is fully functional but is still being actively developed and optimized.

## ✨ Key Features
* **Clean Architecture:** Built on `GameInstanceSubsystem` for proper lifecycle management.
* **Version Migration:** Built-in `MigrateFromVersion` system allows you to update your save data structures without breaking players' old save files.
* **Slot System:** Easy-to-use support for multiple save slots and profiles.
* **Hybrid Workflow:** Written in C++ for performance, but fully accessible via **Blueprints** through a global Static Library.
* **Developer Friendly:** Includes `FirstRunInit` logic to easily set up default values for new players.

## 🤝 Feedback
Since this is my first UE5 plugin, I appreciate any feedback, suggestions, or bug reports. Thank you for checking it out!
