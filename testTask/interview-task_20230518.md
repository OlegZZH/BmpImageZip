## 1.  Бібліотека стискання зображень. 

Постановка задачі.

Є зображення у форматі grayscale (тобто, кожен піксель представлений значеннями від 0 до 255 відтінків сірого), яке містить сторінку тексту

```
struct RawImageData {
int width; // image width in pixels
int height; // image height in pixels
unsigned char * data; // Pointer to image data. data[j * width + i] is color of pixel in row j and column i.
}
```

Таке зображення містить багато білих рядків пікселів (наприклад, поля згори та знизу та міжрядкові інтервали), а також, навіть непусті рядки пікселів, містять багато білих зон. Для оптимізації місця зберігання такого зображення необхідно його закодувати так:

  1. для кожного рядка пікселів зберігати порожній він чи ні в індексі порожніх/непустих рядків (порожній рядок - це рядок, що містить тільки білі пікселі 0xff)
  2. кожний непустий рядок кодувати наступним чином (зліва направо):
     - 4-ри поспіль білих пікселів кодувати 0
     - 4-ри поспіль чорних пікселів кодувати 10
     - будь-яку іншу послідовність 4х пікселів кодувати в 11 + кольори пікселів

Наприклад, якщо ширина картинки 12, то наступний рядок буде вважатися порожнім:
```
0xff 0xff 0xff 0xff 0xff 0xff 0xff 0xff 0xff 0xff 0xff 0xff
```
Тобто йому буде відповідати лише 1-ця в індексі порожніх/непустих рядків.

А рядок пікселів:
```
0xff 0xff 0xff 0xff 0x00 0x00 0x00 0x00 0x01 0x01 0x01 0x01
```
Закодується в (у бінарному вигляді):
```
01011 0000 0001 0000 0001 0000 0001 0000 0001

Как, к примеру, должна выглядеть закодированная ниже строка(width=19) в бинарном виде?

0xff 0xff 0xff 0xff  0xff 0xff 0xff 0xff  0x01 0x01 0x01 0x01  0x00 0x00 0x00 0x00  0xff 0xff 0xff

0011 0000  0001 0000  0001 0000  0001 0000  0001 100(0-padding bit)
   0x30       0x10       0x10       0x10       0x18
0 - 0xff 0xff 0xff 0xff
0 - 0xff 0xff 0xff 0xff
11 0000  0001 0000  0001 0000  0001 0000  0001 - 0x01 0x01 0x01 0x01
10 - 0x00 0x00 0x00 0x00
0 - 0xff 0xff 0xff (padding)
но это для примера, как этот паддинг организовать вы можете решить сами.
```
де перший нуль відповідає 4м білим пікселям, наступні 10 відповідають чорним пікселям з 5 по 8й і залишок 11 ... - відповідають пікселям, що залишилися.

Формат вихідного файлу визначити під час розробки. 

Наприклад, це може бути так (формат бінарний):

ідентифікатор формату - BA
ширина зображення
висота зображення
індекс рядків 
стиснуті дані

але, можливі і інші варіанти формату, як з точки зору розробника є оптимальним.

- Необхідно написати функції кодування та декодування зі структури RawImageData до представлення, описаного у попередньому розділі.
- При розкодуванні закодованого зображення має бути відновлено оригінальне зображення
- результат зберегти у файл з розширенням .barch

Необхідно створити бібліотеку (static або shared - на вибір) з функціональністю сттискання та розтиснення bmp картинки (даних, представлених в структурі RawImageData, яку заповнити в frontend частині додатку). Можливе використання ТІЛЬКИ C++ і STL. Будь-які інші 3rdparty libraries заборонено.
  

##  2. UI стиснення зображень з використанням Qt та QML.
  Дозволяється використовувати тільки C++, STL, Qt, Qt Quick (не заборонено використання Qt Quick Controls 2,  Qt Widgets можливо використовувати лише у разі відсутньості досвіду з QML)
  - Можливість запустити програму з параметром "шлях до директорії" (якщо параметр не вказано або він є не коректним - використовувати поточну директорію, з якої запущено додаток)
  - Бажано реалізувати QML плагін, в який покласти QML компоненти, які будуть використовуватися в додатку (модель, кнопка, діалог). Якщо нема досвіду з QML плагином, то ця вимога не є критичною.
  - Реалізувати C++ модель, яка міститиме в собі перелік файлів (з додатковими атрибутами, наприклад, розмір і т.д.) в поточній директорії (або директорії, заданої параметром командного рядка), якщо є час, то бажано додати можливість фільтрації по розширенню
  - Використовуючи модель з попереднього пункту, відобразити список файлів у вікні програми (просто список файлів у стовпчик) з розмірами. Відображати тільки bmp, png і barch файли
  - При натисканні на список:
    Якщо це .bmp (.barch - закодований) файл, його потрібно закодувати (.barch - потрібно розкодувати), використовуючи бібліотеку з першої частини завдання. Кодувати (розкодувати) потрібно в окремому потоці, при цьому у списку біля імені файлу відображати "Кодується" ("Розкодовується") протягом усього процесу. Ім'я кодованого файлу = ім'я файлу + "packed.barch". Ім'я розкодованого файлу = ім'я файлу + "unpacked.bmp"
    Інакше - потрібно відобразити діалогове вікно з помилкою.
  - Діалогове вікно з помилкою та однією кнопкою "Ок", при натисканні на яку це вікно має закритися. При натисканні кнопка має показати фідбек (наприклад, змінити колір). Таке діалогове вікно повинне завантажуватись не при старті додатку, а тільки тоді, коли його потрібно відобразити. Повідомлення про помилку може бути, наприклад, "Невідомий файл"

##  3. Проект та збірка
  - Використовувати cmake або qmake - на вибір
  - Якщо для збирання програми потрібні додаткові параметри - бажано, щоби був скрипт який збере з потрібними параметрами
  - Програму розмістити на github і надіслати посилання або в локальний репозиторій і надіслати архів

