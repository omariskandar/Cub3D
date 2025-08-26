🕹️ Cub3D – Extended Edition

A 3D maze shooter built with C + MiniLibX, inspired by Wolfenstein 3D (1992).
Extended with shooting mechanics and enemies.

📖 Overview

Cub3D started as a raycasting engine rendering a maze with textures.
We enhanced it with:

Enemies that spawn on the map.

Player shooting system (fire bullets/projectiles).

Enemy AI (basic movement or attack behavior).

Health system (player can take damage, enemies can die).

This makes it a playable FPS prototype 🎯.

🚀 Features

✅ Base features (raycasting, textures, player movement).
✅ Shooting system:

Fire bullets (e.g., with SPACE or CTRL).

Projectile raycast checks if enemy is hit.

Reload / cooldown mechanics.

✅ Enemies:

Spawned via special map characters (M, E, etc.).

Rendered as sprites (billboarding).

Can move/attack.

Take damage and die.

✅ HUD elements:

Ammo / health counters.

Crosshair for aiming.

✅ Extended gameplay:

Player can lose if health reaches 0.

Enemies disappear when killed.

📄 Extended Map Format (.cub)

We added enemy markers:

1111111111111
1000000000001
1011000M00001   ← M = enemy
1001000000001
1000P00000001   ← P = player
1111111111111


P = player start.

M (or E) = enemy spawn.

Still supports walls, floor/ceiling colors, textures.

🎮 Controls
Key	Action
W / S	Move forward/back
A / D	Strafe left/right
Left / Right Arrows	Rotate camera
mouse rotation
left click	Shoot
ESC	Exit

⚙️ Shooting Mechanism

Shooting uses a raycast from player direction.

If the ray intersects with an enemy sprite:

Enemy health is reduced.

If health ≤ 0 → enemy is destroyed.

Add cooldown to prevent spamming.

Can be extended with ammo system.

👾 Enemies

Implemented as sprites → rendered using distance-sorted billboarding.

Basic AI (examples):

Static turrets.

Moving toward the player.

Attacking at close distance.

Each enemy has:

Health points.

Sprite texture(s) (idle, attack, death).

🧑‍💻 Skills Learned (Extra)

Sprite rendering & sorting (painters algorithm).

Sprite hit-detection via raycasting.

Implementing simple AI logic.

Expanding file formats with new entities.

Game loop design (player actions + enemy actions).
