// v=2

const staticCacheName = 'shilov-v1';
const assets = [];

// install event
self.addEventListener('install', evt => {
    evt.waitUntil(
        caches.open(staticCacheName).then(cache => {
            console.log('cache opened');
            return cache.addAll(assets);
        })
    );
});

// activate event
self.addEventListener('activate', evt => {
    evt.waitUntil(
        caches.keys().then(keys => {
            return Promise.all(keys.filter(key => key !== staticCacheName).map(key => caches.delete(key)));
        })
    );
});

// fetch event
self.addEventListener('fetch', evt => {
    evt.respondWith(
        caches.match(evt.request).then(cacheRes => {return cacheRes || fetch(evt.request);})
    );
});