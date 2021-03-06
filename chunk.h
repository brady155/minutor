/** Copyright (c) 2013, Sean Kasun */
#ifndef CHUNK_H_
#define CHUNK_H_

#include <QtCore>
#include <QVector>

#include "./nbt.h"
#include "./entity.h"
#include "./paletteentry.h"
#include "./generatedstructure.h"


class ChunkSection {
 public:
  const PaletteEntry & getPaletteEntry(int x, int y, int z);
  const PaletteEntry & getPaletteEntry(int offset, int y);
  quint8 getSkyLight(int x, int y, int z);
  quint8 getSkyLight(int offset, int y);
  quint8 getBlockLight(int x, int y, int z);
  quint8 getBlockLight(int offset, int y);

  PaletteEntry *palette;
  int        paletteLength;

  quint16 blocks[16*16*16];
//quint8  skyLight[16*16*16/2];   // not needed in Minutor
  quint8  blockLight[16*16*16/2];
};


class Chunk : public QObject {
  Q_OBJECT

 public:
  Chunk();
  ~Chunk();
  void load(const NBT &nbt);

  qint32 get_biome(int x, int z);
  qint32 get_biome(int x, int y, int z);
  qint32 get_biome(int offset);

signals:
  void structureFound(QSharedPointer<GeneratedStructure> structure);

 protected:
  void loadSection1343(ChunkSection *cs, const Tag *section);
  void loadSection1519(ChunkSection *cs, const Tag *section);


  typedef QMap<QString, QSharedPointer<OverlayItem>> EntityMap;

  int version;
  qint32 biomes[16 * 16 * 4];
  int highest;
  ChunkSection *sections[16];
  int renderedAt;
  int renderedFlags;
  bool loaded;
  bool rendering;
  uchar image[16 * 16 * 4];  // cached render: RGBA for 16*16 Blocks
  uchar depth[16 * 16];
  EntityMap entities;
  int chunkX;
  int chunkZ;
  friend class MapView;
  friend class ChunkRenderer;
  friend class ChunkCache;
  friend class WorldSave;
};

#endif  // CHUNK_H_
