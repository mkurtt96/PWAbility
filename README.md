# ⚔️ PW.Ability
> ⚠️ **Development Status:**  
> This module is currently being extracted and refactored from **ProjectW**, a private Unreal Engine 5 prototype.  
> While most systems are functional, interfaces and folder structures may still change as the refactor progresses.  
> The goal is to make this a clean, reusable, standalone module for future Unreal projects.  

**PW.Ability** is a modular Unreal Engine 5 framework providing base classes and utilities for spawning and managing gameplay ability actors such as projectiles and effect actors.

Originally developed as part of **ProjectW**, it is now refactored into a standalone, **GAS-independent** module that integrates seamlessly with other PW systems.

---

## 🧩 Overview

**PW.Ability** provides a consistent foundation for ability-driven gameplay with a focus on clarity, extensibility, and modularity.

- Base actor classes for spell and projectile behavior  
  `AWBaseSpellActor`, `ABaseProjectile`, `ASplineMovementProjectile`, `AMyEffectActor`
- Custom components for movement and VFX handling  
  `USphereNiagaraComponent`, `UWProjectileMovementComponent`
- Optional team-aware targeting when `PW.Teams` is available (`WITH_PWTEAMS`)
- Shared runtime data through `USpellParamsBase` (from `PW.SharedTypes`)
- Fully extensible structure allowing projects to subclass parameters or behaviors

---

## 🧱 Module Dependencies

| Type | Dependencies |
|------|---------------|
| **Public** | Core, PWSharedTypes |
| **Private** | CoreUObject, Engine, Slate, SlateCore, Niagara, PWContracts |
| **Optional** | PWTeams *(auto-detected via WITH_PWTEAMS define)* |

PWAbility automatically detects the presence of **PW.Teams** at build time.  
If found, it enables `WITH_PWTEAMS=1` and adds the module dependency.  
Otherwise, it compiles standalone with `WITH_PWTEAMS=0`.

---

## 🧠 Key Concepts

- **SpellParams-driven logic** : every spawned ability carries a context container derived from `USpellParamsBase`, ensuring consistent and network-safe data passing.
- **Team-aware filtering** : functions like `IsEnemy`, `IsAlly`, and `CheckForCollisionTarget()` adapt based on `WITH_PWTEAMS`.
- **Extensible API** : new actor types or parameter sets can be introduced without modifying the core module.

---

## 🧰 Compatibility

- **Engine:** Unreal Engine 5.3 or newer  
- **Status:** Stable Core / Finalizing  
- **Required PW Modules:**  
  [PW.SharedTypes](https://github.com/mkurtt96/PWCoreLibs)  
  [PW.Contracts](https://github.com/mkurtt96/PWCoreLibs)  
- **Optional Module:**  
  [PW.Teams](https://github.com/mkurtt96/PWTeams)

---

## 📄 License


This project is licensed under the **MIT License**.  
See the [LICENSE](LICENSE) file for full details.

---

## 👤 Author

**Metehan Goksel Kurtulan**  
Game Developer — Systems & Gameplay Engineering  
